#include "floatingwidget.h"

#include <QGraphicsBlurEffect>
#include <qpainter.h>

#include "../palette.h"

namespace PIPKA::UI {

FloatingWidget::FloatingWidget(
        const int &x, const int &y,
        const int &w, const int &h,
        QWidget *parent)
    : QWidget{parent}
{
    // setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    resize(w, h);
    move(x, y);
}

void FloatingWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Palette::BASE);
    painter.setBackground(Palette::BASE);
    constexpr int radius = 20;
    painter.drawRoundedRect(this->rect(), radius, radius);
    // painter.fillRect(this->rect(),));
}

}
