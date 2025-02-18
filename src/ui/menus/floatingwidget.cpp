#include "floatingwidget.h"

#include <QGraphicsBlurEffect>
#include <qpainter.h>

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
    painter.setBrush(QColor(0xFF2C2C2C));
    painter.setBackground(QColor(0xFF2C2C2C));
    constexpr int radius = 20;
    painter.drawRoundedRect(this->rect(), radius, radius);
    // painter.fillRect(this->rect(),));
}

}
