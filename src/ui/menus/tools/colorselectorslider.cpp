#include "colorselectorslider.h"

#include <QMouseEvent>
#include <QPainter>

#include "../../palette.h"

namespace PIPKA::UI {
ColorSelectorSlider::ColorSelectorSlider(
    const float bottomLimit,
    const float topLimit,
    QWidget *parent) :
    QWidget(parent),
    m_bottomLimit(bottomLimit),
    m_topLimit(topLimit)
{
    m_pressed = false;
    initUI();
}

void ColorSelectorSlider::initUI()
{
    setFixedSize(200, 14);
    m_position = this->height();
}

void ColorSelectorSlider::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    const QRect lineRect = this->rect();
    const QRect selectorRect(
        m_position - height() / 2,
        0,
        height(),
        height());

    painter.setBrush(Palette::NON_ACTIVE);
    painter.setPen(Palette::NON_ACTIVE);
    painter.drawRoundedRect(lineRect, height() / 2, height() / 2);

    painter.setPen(QPen(Palette::WHITE, 2));
    painter.drawEllipse(selectorRect.adjusted(2, 2, -2, -2));
}

void ColorSelectorSlider::mousePressEvent(QMouseEvent *event)
{
    m_pressed = true;
    m_position = event->pos().x();
    m_position = std::clamp(
        m_position,
        static_cast<float>(height() / 2),
        static_cast<float>(width() - height() / 2));
    calculateValue();
    update();
}

void ColorSelectorSlider::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;
}

void ColorSelectorSlider::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_pressed) return;

    m_position = event->pos().x();
    m_position = std::clamp(
        m_position,
        static_cast<float>(height() / 2),
        static_cast<float>(width() - height() / 2));
    calculateValue();
    update();
}

void ColorSelectorSlider::calculateValue()
{
    m_value = mapPosition(m_position);
    qDebug() << m_value;
    emit valueChanged(m_value);
}

float ColorSelectorSlider::mapPosition(float position) const
{
    position -= this->height() / 2;
    position /= (this->width() - this->height());
    const float range = m_topLimit - m_bottomLimit;
    position = position * range + m_bottomLimit;
    return position;
}
}
