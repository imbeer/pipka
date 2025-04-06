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

Window::~Window()
{
    if (m_eventHandler)
        delete m_eventHandler;
}

void Window::initUi()
{
    const auto centralWidget = new QWidget(); // not leak, because set as central widget
    setCentralWidget(centralWidget);
    setMinimumSize(800, 500);
    centralWidget->setLayout(new QBoxLayout(QBoxLayout::LeftToRight));
}

void Window::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    for (const auto &menu : m_menus) {
        menu->onWindowResize(event->size());
    }
    if (m_eventHandler)
        m_eventHandler->setSize(event->size().width(), event->size().height());
}

void Window::setController(std::shared_ptr<CONTROL::Controller> &controller)
{
    m_eventHandler = new EventHandler(controller, width(), height());
    const auto canvas = new CanvasWidget(controller, m_eventHandler);
    setCentralWidget(canvas);
    canvas->setFocus();
    canvas->setFocusPolicy(Qt::FocusPolicy::WheelFocus);
    const auto menu = std::make_shared<MainToolBar>(controller, 20, 20, 256, 1000, this);
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
