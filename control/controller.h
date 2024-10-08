#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "transform.h"
#include "../picture/picture.h"

using namespace PICTURE;

namespace CONTROL {

class Controller
{

Q_OBJECT
public:
    Controller();
    Controller(const int w, const int h);
    inline Transform transform() {return m_transform;};
    inline Picture picture() {return m_picture;};
    void handleEvnet(QEvent *event);

private:
    Transform m_transform;
    Picture m_picture;
};

}
#endif // CONTROLLER_H
