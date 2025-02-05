#include "eventhandler.h"

namespace PIPKA::UI {

EventHandler::EventHandler(
    std::shared_ptr<PIPKA::CONTROL::Controller> &controller,
    const int &width, const int &height)
    : m_controller(controller), width(width), height(height)
{}

void EventHandler::tabletEvent(QTabletEvent *event)
{
    auto point = getNormalizedClickVector(event->position(), event->pressure());
    //
    switch (event->type()) {
    case QEvent::TabletPress:
        m_controller->handleClick(point.x(), point.y(), point.z());
        break;
    case QEvent::TabletRelease:
        m_controller->handleRelease(point.x(), point.y(), point.z());
        break;
    case QEvent::TabletMove:
        m_controller->handleMove(point.x(), point.y(), point.z());
        break;
    default:
        break;
    }
}

void EventHandler::wheelEvent(QWheelEvent *event)
{
    int delta = event->angleDelta().y();  // Get scroll amount

    if (delta > 0) {
        m_controller->scaleUp();
    } else {
        m_controller->scaleDown();
    }
}

void EventHandler::mousePressEvent(QMouseEvent *event)
{
    auto point = getNormalizedClickVector(event->position());
    m_controller->handleClick(point.x(), point.y(), point.z());
}

void EventHandler::mouseReleaseEvent(QMouseEvent *event)
{
    auto point = getNormalizedClickVector(event->position());
    m_controller->handleRelease(point.x(), point.y(), point.z());
}

void EventHandler::mouseMoveEvent(QMouseEvent *event)
{
    auto point = getNormalizedClickVector(event->position());
    m_controller->handleMove(point.x(), point.y(), point.z());
}

void EventHandler::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    switch (key) {
    case Qt::Key_R:
        m_controller->rotateRight();
        break;
    case Qt::Key_Q:
        m_controller->rotateLeft();
        break;
    case Qt::Key_S:
        if (m_pressedKeys.count(Qt::Key_Control) > 0) {
            qDebug() << "saving";
            m_controller->saveImage();
        } else {
            m_controller->moveUp();
        }
        break;
    case Qt::Key_W:
        m_controller->moveDown();
        break;
    case Qt::Key_D:
        m_controller->moveLeft();
        break;
    case Qt::Key_A:
        m_controller->moveRight();
        break;
    case Qt::Key_Backspace:
        m_controller->clearActiveLayer();
        break;
    case Qt::Key_L:
        m_controller->addLayer();
        break;
    default:
        break;
    }
    m_pressedKeys.emplace(key);
}

void EventHandler::keyReleaseEvent(QKeyEvent *event)
{
    m_pressedKeys.erase(m_pressedKeys.find(event->key()));
}

}
