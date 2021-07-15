#include "thumbnail_item.h"
#include <QIcon>

QVariant thumbnail_item::data(int role) const
{
//  if (role == Qt::DecorationRole) {
//    QIcon i = super::icon();
//    if (i.isNull()) {

//      /*
//       * The existing thumbnail (if any) is empty so create one
//       * from the file name and use it -- remembering to call
//       * setIcon so we don't need to go through all this again
//       * next time.
//       */
//      i = QIcon(data(Qt::DisplayRole));
//      setIcon(i);
//    }
//    return(i); --- qt 4.8
//  }
  return(super::data(role));
}
