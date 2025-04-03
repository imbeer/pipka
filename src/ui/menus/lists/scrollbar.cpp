#include "scrollbar.h"

#include <QPainter>
#include <QStyleOptionSlider>
#include "../../palette.h"

namespace PIPKA::UI
{

ScrollBar::ScrollBar(
        const Qt::Orientation orientation,
        QWidget *parent) :
    QScrollBar(orientation, parent)
{
    if (orientation == Qt::Horizontal) {
        setFixedHeight(5);
    } else {
        setFixedWidth(5);
    }
}

void ScrollBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QStyleOptionSlider opt;
    initStyleOption(&opt);

    const int pageStep = this->pageStep();

    if (this->maximum() == this->minimum()) {
        return;
    }

    const QRect handleRect = style()->subControlRect(QStyle::CC_ScrollBar, &opt, QStyle::SC_ScrollBarSlider, this);
    const QRect fullRect = this->rect();

    painter.setPen(QPen(Palette::DEFAULT, 2));
    painter.setBrush(Palette::BASE);
    painter.drawRoundedRect(handleRect, 5, 5);
}

}