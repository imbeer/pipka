#include "brushitemdelegate.h"

#include <QPainter>
#include <QPainterPath>
#include "../../palette.h"

namespace PIPKA::UI
{

BrushItemDelegate::BrushItemDelegate(QObject *parent) :
    ListItemDelegate(parent)
{}

void BrushItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    const QVariant data = index.data(Qt::DisplayRole);

    if (!data.canConvert<QVariantMap>())
        throw std::bad_cast();
    QVariantMap dataMap = data.toMap();

    const QString text = dataMap["text"].toString();
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
        marginedRect.adjusted(3, 5, -10, -5),
        Qt::AlignVCenter | Qt::AlignLeft,
        text);

    static QPixmap openEyePixmap(":/brush.png");
    painter->drawPixmap(buttonRectangle(option), openEyePixmap);
}

}
