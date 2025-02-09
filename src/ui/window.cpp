#include "window.h"

#include "canvaswidget.h"

#include <QBoxLayout>

namespace PIPKA::UI {

Window::Window(QWidget *parent)
    : QMainWindow{parent}
{
    initUi();
}

void Window::initUi()
{
    // setWindowFlags(Qt::FramelessWindowHint);
    QWidget *centralWidget = new QWidget();
    setCentralWidget(centralWidget);
    // centralWidget->setLayout(new QBoxLayout(QBoxLayout::LeftToRight));
}

void Window::setController(std::shared_ptr<PIPKA::CONTROL::Controller> &controller)
{
    auto canvas = new CanvasWidget(controller);
    // centralWidget()->layout()->addWidget(canvas);
    setCentralWidget(canvas);
}

}
