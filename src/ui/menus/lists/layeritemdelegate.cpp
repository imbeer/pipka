#include "layeritemdelegate.h"

#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>

#include "../../palette.h"

namespace PIPKA::UI {

LayerItemDelegate::LayerItemDelegate(QObject *parent)
    : QAbstractItemDelegate(parent)
{}

void LayerItemDelegate::paint(
    QPainter *painter,
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    const QString text = index.data(Qt::DisplayRole).toString();
    const auto marginedRect = option.rect.adjusted(0, 5, 0, -5);
    painter->setPen(Qt::NoPen);

    QPainterPath path;
    path.addRoundedRect(marginedRect, 10, 10);

    if (option.state & QStyle::State_Selected) {
        QLinearGradient gradient(option.rect.topLeft(), option.rect.topRight());
        gradient.setColorAt(0.0, Palette::NON_ACTIVE);
        gradient.setColorAt(1.0, Palette::BASE);
        painter->fillPath(path, gradient);
    } else {
        painter->fillPath(path, Palette::BASE);
    }

    painter->setPen(Palette::WHITE);
    painter->setFont(QFont("Arial", 12, QFont::Bold));
    painter->drawText(
        marginedRect.adjusted(10, 5, -10, -5),
        Qt::AlignVCenter | Qt::AlignLeft,
        text);
    painter->setBrush(Palette::WHITE);
    painter->drawEllipse(getHideButtonRect(option));
}

QSize LayerItemDelegate::sizeHint(
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return {235, 40};
}

bool LayerItemDelegate::editorEvent(
    QEvent* event,
    QAbstractItemModel* model,
    const QStyleOptionViewItem& option,
    const QModelIndex& index)
{
    if (event->type() == QEvent::MouseButtonPress) {
        if (const auto* mouseEvent = dynamic_cast<QMouseEvent*>(event);
            getHideButtonRect(option).contains(mouseEvent->pos())) {
            emit hideButtonClicked(index);
            return true;
        }
    }
    return false;
}

QRect LayerItemDelegate::getHideButtonRect(const QStyleOptionViewItem &option)
{
    return option.rect.adjusted(195, 10, -20, -10);
}

}
