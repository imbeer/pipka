#include "window.h"

#include "canvaswidget.h"
// #include "menus/floatingwidget.h"
#include "menus/maintoolbar.h"

#include <QBoxLayout>

namespace PIPKA::UI {

Window::Window(QWidget *parent)
    : QMainWindow{parent}
{
    initUi();
}

void Window::initUi()
{
    // startSystemMove();
    // setWindowFlags(Qt::FramelessWindowHint);
    auto centralWidget = new QWidget();
    setCentralWidget(centralWidget);
    setMinimumSize(800, 500);
    centralWidget->setLayout(new QBoxLayout(QBoxLayout::LeftToRight));
}

void Window::setController(std::shared_ptr<PIPKA::CONTROL::Controller> &controller)
{
    const auto canvas = new CanvasWidget(controller);
    // centralWidget()->layout()->addWidget(canvas);
    setCentralWidget(canvas);
    canvas->setFocus();
    canvas->setFocusPolicy(Qt::StrongFocus);
    const auto menu = std::make_shared<MainToolBar>(controller, 10, 10, 256, 1000, this);
    m_menus.push_back(menu);
    menu->show();
}

// void Window::moveEvent(QMoveEvent *event)
// {
//     QPoint newPos = this->pos();
//     qDebug() << "Window moved to:" << newPos.x() << newPos.y();

//     for (auto &menu : m_menus) {
//         menu->raise();
//         menu->move(menu->pos() + (event->pos() - event->oldPos()));
//     }
//     QMainWindow::moveEvent(event);
// }

}
