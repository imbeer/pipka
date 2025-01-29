#include "controller.h"
#include <qdebug.h>

namespace PIPKA::CONTROL {

Controller::Controller()
    : m_image(std::nullopt)
{
    updateTransform();
}

void Controller::createImage(const int &w, const int &h)
{
    if (!m_image.has_value()) {
        m_image.emplace(w, h);
    } else {
        qDebug() << "image already exists";
    }
}

void Controller::scaleUp()
{
    scaleX += 0.1f;
    scaleY += 0.1f;
    updateTransform();
}

void Controller::scaleDown()
{
    scaleX -= 0.1f;
    scaleY -= 0.1f;
    updateTransform();
}

void Controller::updateTransform()
{
    m_transform(0, 0) = scaleX * cos(rotation);  m_transform(0, 1) = -scaleY * sin(rotation);   m_transform(0, 2) = moveX;
    m_transform(1, 0) = scaleX * sin(rotation);  m_transform(1, 1) = scaleY * cos(rotation);    m_transform(1, 2) = moveY;
    m_transform(2, 0) = 0.0f;                    m_transform(2, 1) = 0.0f;                      m_transform(2, 2) = 1.0f;
}

}
