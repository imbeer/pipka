#include "listitemdelegate.h"

#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>

#include "../../palette.h"

namespace PIPKA::UI {

ListItemDelegate::ListItemDelegate(QObject *parent) :
    QAbstractItemDelegate(parent)
{}

void ListItemDelegate::paint(
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
    painter->setFont(Palette::MENUFONT);
    painter->drawText(
        marginedRect.adjusted(5, 5, -10, -5),
        Qt::AlignVCenter | Qt::AlignLeft,
        text);

    // todo: icon render
    if (isVisible) {
        // qDebug() << "ListItemDelegate::paint::isVisible";
        static QPixmap openEyePixmap(":/opened_eye.png");
        painter->drawPixmap(buttonRectangle(option), openEyePixmap);
    } else {
        static QPixmap closedEyePixmap(":/closed_eye.png");
        painter->drawPixmap(buttonRectangle(option), closedEyePixmap);
        // qDebug() << "ListItemDelegate::paint::is not visible";
    }
}

QSize ListItemDelegate::sizeHint(
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return {230, 40};
}

bool ListItemDelegate::editorEvent(
    QEvent* event,
    QAbstractItemModel* model,
    const QStyleOptionViewItem& option,
    const QModelIndex& index)
{
    if (event->type() == QEvent::MouseButtonPress) {
        if (const auto* mouseEvent = dynamic_cast<QMouseEvent*>(event);
            clickableButtonRectangle(option).contains(mouseEvent->pos())) {
            emit buttonClicked(index);
            return true;
        }
    }
    return false;
}

QRect ListItemDelegate::buttonRectangle(const QStyleOptionViewItem &option)
{
    QRect rect(0, 0, 18, 13);
    rect.moveTo(option.rect.x() + 182, option.rect.y() + 14);
    return rect;
}

QRect ListItemDelegate::clickableButtonRectangle(const QStyleOptionViewItem &option)
{
    return buttonRectangle(option).adjusted(-11, -14, 13, 11);
}

}
