#include "controller.h"

namespace CONTROL {

Controller::Controller()
{}

Controller::Controller(const int w, const int h) : m_picture(w, h)
{
    m_transform = Transform();
}

void Controller::handleEvnet(QEvent *event)
{

}
}
