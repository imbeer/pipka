#ifndef LAYERITEMDELEGATE_H
#define LAYERITEMDELEGATE_H

#include <QAbstractItemDelegate>


namespace PIPKA::UI {

class LayerItemDelegate : public QAbstractItemDelegate
{
    Q_OBJECT

public:
    explicit LayerItemDelegate(QObject *parent = nullptr);

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

private:
    static QRect getHideButtonRect(const QStyleOptionViewItem &option);

signals:
    void hideButtonClicked(const QModelIndex& index);

};

}

#endif // LAYERITEMDELEGATE_H
