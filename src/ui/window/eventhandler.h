#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "../../control/controller.h"

#include <qevent.h>
#include <unordered_set>
#include <QShortcut>

namespace PIPKA::UI {

class EventHandler
{
public:
    EventHandler(
        const std::shared_ptr<CONTROL::Controller> &controller,
        const int &width, const int &height);

    void tabletEvent      (QTabletEvent *event);
    void wheelEvent       (QWheelEvent  *event);
    void mousePressEvent  (QMouseEvent  *event);
    void mouseReleaseEvent(QMouseEvent  *event);
    void mouseMoveEvent   (QMouseEvent  *event);
    void keyPressEvent    (QKeyEvent    *event);
    void keyReleaseEvent  (QKeyEvent    *event);

    void setSize(const int &width, const int &height) {this->width = width; this->height = height;};

    QVector3D getNormalizedClickVector(const QPointF &position, const double &pressure = 1) const
    {
        return {
            static_cast<float>(2.0 * position.x() / width - 1.0),
            static_cast<float>(1.0 - 2.0 * position.y() / height),
            static_cast<float>(pressure)};
    };

private:
    std::shared_ptr<CONTROL::Controller> m_controller;
    std::unordered_set<int> m_pressedKeys;
    int width;
    int height;
};

}

#endif // EVENTHANDLER_H
