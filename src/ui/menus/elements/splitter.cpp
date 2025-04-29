#include "splitter.h"
#include <QPainter>

#include "../../palette.h"

namespace PIPKA::UI {

Splitter::Splitter(
    QWidget *parent,
    const int width,
    const int height,
    const int thickness) :
QWidget(parent), m_thickness(thickness)
{
    setMinimumSize(QSize(width, height));
}

void Splitter::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setBrush(Palette::NON_ACTIVE);
    painter.setPen(Palette::NON_ACTIVE);

    const int margin = (this->height() - this->m_thickness) * 0.5;
    const QRect rect = this->rect().adjusted(0, +margin, 0, -margin);
    painter.drawRect(rect);
}
}
