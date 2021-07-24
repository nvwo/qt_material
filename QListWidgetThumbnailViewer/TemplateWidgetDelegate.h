#include <QStyledItemDelegate>
#include <QPainter>
template <class T>
class WidgetDelegate : public QStyledItemDelegate{
#ifdef Q_COMPILER_STATIC_ASSERT
    static_assert(std::is_base_of<QWidget,T>::value,"Template argument must be a QWidget");
#endif
    Q_DISABLE_COPY(WidgetDelegate)
public:
    explicit WidgetDelegate(QObject* parent = Q_NULLPTR)
        :QStyledItemDelegate(parent)
        , m_baseWid(new T)
    {}
    ~WidgetDelegate(){
        delete m_baseWid;
    }
    void paint(QPainter *painter, const QStyleOptionViewItem &option,const QModelIndex &index) const Q_DECL_OVERRIDE{
        setSubEditorData(m_baseWid,index);
        m_baseWid->resize(option.rect.size());
        QPixmap pixmap(option.rect.size());
        m_baseWid->render(&pixmap);
        painter->drawPixmap(option.rect,pixmap);
    }
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE{
        Q_UNUSED(option);
        setSubEditorData(m_baseWid,index);
        return m_baseWid->sizeHint();
    }
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE Q_DECL_FINAL {
        Q_UNUSED(option);
        Q_UNUSED(index);
        T* editor = new T;
        editor->setParent(parent);
        return editor;
    }
    virtual void setSubEditorData(T* editor, const QModelIndex &index) const =0;
    void setEditorData(QWidget* editor, const QModelIndex &index) const Q_DECL_OVERRIDE Q_DECL_FINAL {
        T* subEdit = qobject_cast<T*>(editor);
        Q_ASSERT(subEdit);
        return setSubEditorData(subEdit,index);
    }
private:
    T* m_baseWid;
};

// An example usage would be:
#include <QLabel>
class LabelDelegate : public WidgetDelegate<QLabel>{
    Q_OBJECT
    Q_DISABLE_COPY(LabelDelegate)
public:
    explicit LabelDelegate(QObject* parent=Q_NULLPTR)
        :WidgetDelegate<QLabel>(parent)
    {}
    void setSubEditorData(QLabel* editor, const QModelIndex &index) const Q_DECL_OVERRIDE{
        editor->setText("Content: <b>" + displayText(index.data(), editor->locale()) + "</b>");
    }
};

//int main(int argc, char *argv[])
//{

//    QApplication app(argc,argv);
//    QListWidget w;
//    w.model()->insertColumns(0,2);
//    w.model()->insertRows(0,2);
//    w.model()->setData(w.model()->index(0,0),"0,0");
//    w.model()->setData(w.model()->index(1,0),"1,0");
//    LabelDelegate* tempDelegate = new LabelDelegate(&w);
//    w.setItemDelegate(tempDelegate);
//    w.show();
//    return app.exec();
//}
