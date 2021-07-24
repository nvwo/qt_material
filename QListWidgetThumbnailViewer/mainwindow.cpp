#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QList>
#include <QListWidget>
#include <QStandardItem>
#include "TemplateWidgetDelegate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->setViewMode(QListWidget::IconMode);
    ui->listWidget->setIconSize(QSize(280,150));
    ui->listWidget->setResizeMode((QListWidget::Adjust));
    for(int i=1;i<20;i++)
    {
        QString path = "E:/dev8/qtest_guides/QListWidgetThumbnailViewer/images/" + QString::number(1) + ".png";
        QListWidgetItem *item = new QListWidgetItem(QIcon(path),QString("Image" + QString::number(i) + ".png" ));
        ui->listWidget->addItem(item);
    }
    //====
    QStandardItem * s1;
    QStandardItem * s2;
    QStandardItem *s3;

    QStandardItemModel * model = new QStandardItemModel(this);
    QList<QStandardItem *> list;
    list.push_back(new QStandardItem(QIcon("../QListWidgetThumbnailViewer/images/1.png"),"1"));//QString("01")
    model->appendRow(list);
    //model->item(0,0)->setIcon(QIcon("../QListWidgetThumbnailViewer/images/1.png"));

    ui->listView->setIconSize(QSize(200,50));
    ui->listView->setGridSize(QSize(20,20));
    ui->listView->setLayoutDirection(Qt::LeftToRight);
    ui->listView->setMovement(QListView::Static);
    s1 = new QStandardItem (QIcon( "../QListWidgetThumbnailViewer/images/1.png"), "2");
    s2 = new QStandardItem (QIcon( "../QListWidgetThumbnailViewer/images/1.png"), "3");

    model->appendColumn(QList<QStandardItem*>{s1,s2});
    model->appendColumn(QList<QStandardItem*>{s2,s1});
    ui->listView->setModel(model);

    //====
    ui->listWidget_2->model()->insertColumns(0,2);
    ui->listWidget_2->model()->insertRows(0,2);
    ui->listWidget_2->model()->setData(ui->listWidget_2->model()->index(0,0),"0,0");
    ui->listWidget_2->model()->setData(ui->listWidget_2->model()->index(1,0),"1,0");
    LabelDelegate* tempDelegate = new LabelDelegate(ui->listWidget_2);
    ui->listWidget_2->setItemDelegate(tempDelegate);
  //      w.show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

