#include "canvaswidget.h"

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{}

CanvasWidget::~CanvasWidget() {}

void CanvasWidget::tabletEvent(QTabletEvent *event)
{
    qDebug() << event->pressure();
}
