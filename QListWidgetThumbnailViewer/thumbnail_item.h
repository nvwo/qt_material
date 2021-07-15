#ifndef THUMBNAIL_ITEM_H
#define THUMBNAIL_ITEM_H
#include <QListWidgetItem>

class thumbnail_item: public QListWidgetItem {
  using super = QListWidgetItem;
public:
  explicit thumbnail_item (const QString &filename)
    : super(filename)
    {}
  virtual QVariant data (int role) const override;
};



#endif // THUMBNAIL_ITEM_H
