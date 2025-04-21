#ifndef LAYERITEMDELEGATE_H
#define LAYERITEMDELEGATE_H

#include <QAbstractItemDelegate>


namespace PIPKA::UI {

class ListItemDelegate : public QAbstractItemDelegate
{
    Q_OBJECT

public:
    explicit ListItemDelegate(QObject *parent = nullptr);

    void paint(
        QPainter *painter,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const override;
    [[nodiscard]] QSize sizeHint(
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const override;

    bool editorEvent(
        QEvent* event,
        QAbstractItemModel* model,
        const QStyleOptionViewItem& option,
        const QModelIndex& index) override;

protected:
    static QRect buttonRectangle(const QStyleOptionViewItem &option);
    static QRect clickableButtonRectangle(const QStyleOptionViewItem &option);

signals:
    void buttonClicked(const QModelIndex& index);
};

}

#endif // LAYERITEMDELEGATE_H
