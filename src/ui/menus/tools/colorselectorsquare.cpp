#include "colorselectorsquare.h"

#include <QMouseEvent>
#include <QPainter>

#include "../../palette.h"

namespace PIPKA::UI
{
ColorSelectorSquare::ColorSelectorSquare(
    QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(200, 200);
}

void ColorSelectorSquare::setHue(const float hue)
{
    m_hue = hue;
    update();
}

void ColorSelectorSquare::setLastPos(QPointF position)
{
    position.setY(std::clamp(position.y(), 0.0, 200.0));
    position.setX(std::clamp(position.x(), 0.0, 200.0));
    m_lastPos = position;
}

void ColorSelectorSquare::mousePressEvent(QMouseEvent *event)
{
    m_pressed = true;
    setLastPos(event->pos());
    update();
    calculateColorOnClick();
}

void ColorSelectorSquare::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;
}

void ColorSelectorSquare::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_pressed) return;
    setLastPos(event->pos());
    update();
    calculateColorOnClick();
}

void ColorSelectorSquare::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    const int width = this->width();
    const int height = this->height();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const float saturation = static_cast<float>(x) / width;
            const float value = 1 - static_cast<float>(y) / height;
            QColor color = QColor::fromHsvF(m_hue, saturation, value);
            painter.setPen(color);
            painter.drawPoint(x, y);
        }
    }

    // painter.setBrush(Palette::WHITE);
    painter.setPen(QPen(Palette::WHITE, 2));
    painter.drawEllipse(QRect(m_lastPos.x() - 5, m_lastPos.y() - 5, 10, 10));
}

void ColorSelectorSquare::calculateColorOnClick()
{
    const int width = this->width();
    const int height = this->height();
    const float x = m_lastPos.x();
    const float y = m_lastPos.y();
    const float saturation = static_cast<float>(x) / width;
    const float value = 1 - static_cast<float>(y) / height;
    emit colorSelected(saturation, value);
}
}
