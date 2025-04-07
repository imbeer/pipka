#include "eventhandler.h"

namespace PIPKA::UI
{
EventHandler::EventHandler(
    const std::shared_ptr<PIPKA::CONTROL::Controller> &controller,
    const int &width, const int &height)
: m_controller(controller), width(width), height(height)
{

}

void EventHandler::tabletEvent(QTabletEvent *event)
{
    const auto point = getNormalizedClickVector(event->position(), event->pressure());
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
    int delta = event->angleDelta().y(); // Get scroll amount
    if (delta > 0) {
        m_controller->transform()->scaleUp();
    } else {
        m_controller->transform()->scaleDown();
    }
}

void EventHandler::mousePressEvent(QMouseEvent *event)
{
    const auto point = getNormalizedClickVector(event->position());
    m_controller->handleClick(point.x(), point.y(), point.z());
}

void EventHandler::mouseReleaseEvent(QMouseEvent *event)
{
    const auto point = getNormalizedClickVector(event->position());
    m_controller->handleRelease(point.x(), point.y(), point.z());
}

void EventHandler::mouseMoveEvent(QMouseEvent *event)
{
    const auto point = getNormalizedClickVector(event->position());
    m_controller->handleMove(point.x(), point.y(), point.z());
}

void EventHandler::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    switch (key) {
        case Qt::Key_R:
            m_controller->transform()->rotateRight();
            break;
        case Qt::Key_Q:
            m_controller->transform()->rotateLeft();
            break;
        case Qt::Key_S:
            if (m_pressedKeys.count(Qt::Key_Control) > 0) {
                qDebug() << "saving";
                m_controller->saveImage();
            } else {
                m_controller->transform()->moveUp();
            }
            break;
        case Qt::Key_W:
            m_controller->transform()->moveDown();
            break;
        case Qt::Key_D:
            m_controller->transform()->moveLeft();
            break;
        case Qt::Key_A:
            m_controller->transform()->moveRight();
            break;
        case Qt::Key_Backspace:
            m_controller->clearActiveLayer();
            break;
        case Qt::Key_L:
            m_controller->image()->pushBackLayer();
            break;
        case Qt::Key_Z:
            if (m_pressedKeys.contains(Qt::Key_Control) && m_pressedKeys.contains(Qt::Key_Shift)) {
                m_controller->versionControl()->redo();
            } else if (m_pressedKeys.contains(Qt::Key_Control)) {
                m_controller->versionControl()->undo();
            }
            break;
        default:
            break;
    }
    m_pressedKeys.emplace(key);
}

void EventHandler::keyReleaseEvent(QKeyEvent *event)
{
    if (auto it = m_pressedKeys.find(event->key()); it != m_pressedKeys.end()) {
        m_pressedKeys.erase(it);
    }
}
}
