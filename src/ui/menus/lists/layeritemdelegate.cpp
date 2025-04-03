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

    const QVariant data = index.data(Qt::DisplayRole);

    if (!data.canConvert<QVariantMap>())
        throw std::bad_cast();
    QVariantMap dataMap = data.toMap();

    const QString text = dataMap["text"].toString();
    const bool isVisible = dataMap["isVisible"].toBool();
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
        marginedRect.adjusted(20, 5, -10, -5),
        Qt::AlignVCenter | Qt::AlignLeft,
        text);

    // todo: icon render
    if (isVisible) {
        // qDebug() << "LayerItemDelegate::paint::isVisible";
        static QPixmap openEyePixmap(":/opened_eye.png");
        painter->drawPixmap(getHideButtonRect(option), openEyePixmap);
    } else {
        static QPixmap closedEyePixmap(":/closed_eye.png");
        painter->drawPixmap(getHideButtonRect(option), closedEyePixmap);
        // qDebug() << "LayerItemDelegate::paint::is not visible";
    }
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
            getClickableHideButtonRect(option).contains(mouseEvent->pos())) {
            emit hideButtonClicked(index);
            return true;
        }
    }
    return false;
}

QRect LayerItemDelegate::getHideButtonRect(const QStyleOptionViewItem &option)
{
    return option.rect.adjusted(200, 14, -17, -13);
}

QRect LayerItemDelegate::getClickableHideButtonRect(const QStyleOptionViewItem &option)
{
    return getHideButtonRect(option).adjusted(-11, -14, 13, 11);
}

}
