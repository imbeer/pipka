#include "menubutton.h"

#include <QPainter>
#include <QPainterPath>
#include "../../../palette.h"

namespace PIPKA::UI
{

MenuButton::MenuButton(
    const int width,
    const int height,
    const int radius,
    const QString &text,
    QWidget *parent) :
    QWidget(parent),
    m_radius(radius),
    m_text(text)
{
    setFixedSize(width, height);
    setAttribute(Qt::WA_Hover, true);
}

void MenuButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    const auto rect = this->rect();
    QPainterPath path;
    path.addRoundedRect(rect, m_radius, m_radius);
    if (underMouse()) {
        QLinearGradient gradient(rect.topLeft(), rect.topRight());
        gradient.setColorAt(0.0, Palette::NON_ACTIVE);
        gradient.setColorAt(1.0, Palette::BASE);
        painter.fillPath(path, gradient);
    }

    painter.setBrush(Palette::ACTIVE);
    painter.setFont(Palette::MENUFONT);
    painter.drawText(
        rect.adjusted(5, 5, -10, -5),
        Qt::AlignVCenter | Qt::AlignLeft,
        m_text);
}

void MenuButton::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
}

void MenuButton::mouseReleaseEvent(QMouseEvent *event)
{
    emit pressed();
}
}
