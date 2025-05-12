#ifndef BRUSHITEMDELEGATE_H
#define BRUSHITEMDELEGATE_H

#include "../listitemdelegate.h"

namespace PIPKA::UI
{

class BrushItemDelegate : public ListItemDelegate {
    Q_OBJECT

public:
    explicit BrushItemDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

}

#endif //BRUSHITEMDELEGATE_H
