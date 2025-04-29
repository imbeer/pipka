#include "iconbutton.h"

#include <QPainter>

namespace PIPKA::UI
{

IconButton::IconButton(
    int width,
    int height,
    int iconWidth,
    int iconHeight,
    const QPixmap &icon,
    QWidget *parent) :
    QWidget(parent),
    m_icon(icon),
    m_iconWidth(iconWidth),
    m_iconHeight(iconHeight)
{
    setFixedSize({width, height});
}

void IconButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    const int xMargin = (width() - m_iconWidth) / 2;
    const int yMargin = (height() - m_iconWidth) / 2;
    const QRect rect = {xMargin, yMargin, m_iconWidth, m_iconHeight};
    painter.drawPixmap(rect, m_icon);
}

void IconButton::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
}

void IconButton::mouseReleaseEvent(QMouseEvent *event)
{
    emit pressed();
}

}
