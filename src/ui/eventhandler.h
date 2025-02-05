#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "../controller/controller.h"

#include <qevent.h>

namespace PIPKA::UI {

class EventHandler
{
public:
    EventHandler(
        std::shared_ptr<PIPKA::CONTROL::Controller> &controller,
        const int &width, const int &height);

    void tabletEvent      (QTabletEvent *event);
    void wheelEvent       (QWheelEvent  *event);
    void mousePressEvent  (QMouseEvent  *event);
    void mouseReleaseEvent(QMouseEvent  *event);
    void mouseMoveEvent   (QMouseEvent  *event);
    void keyPressEvent    (QKeyEvent    *event);
    void resizeEvent      (QResizeEvent *event);

    inline void setSize(const int &width, const int &height) {this->width = width; this->height = height;};

    inline QVector3D getNormalizedClickVector(const QPointF &position, const double &pressure = 1)
    {
        return QVector3D(
            2.0 * position.x() / width - 1.0,
            1.0 - 2.0 * position.y() / height,
            pressure);
    };

private:
    std::shared_ptr<PIPKA::CONTROL::Controller> m_controller;
    int width;
    int height;
};

}

#endif // EVENTHANDLER_H
