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

void Controller::rotateLeft()
{
    angle += 0.1f;
    if (angle > 2 * M_PI)
        angle -= 2 * M_PI;
    updateTransform();
}

void Controller::rotateRight()
{
    angle -= 0.1f;
    if (angle < -2 * M_PI)
        angle += 2 * M_PI;
    updateTransform();
}

void Controller::updateTransform()
{
    m_transform(0, 0) = scaleX * cos(angle);  m_transform(0, 1) = -scaleY * sin(angle);   m_transform(0, 2) = moveX;
    m_transform(1, 0) = scaleX * sin(angle);  m_transform(1, 1) = scaleY * cos(angle);    m_transform(1, 2) = moveY;
    m_transform(2, 0) = 0.0f;                    m_transform(2, 1) = 0.0f;                      m_transform(2, 2) = 1.0f;
}

void Controller::moveLeft()
{
    moveX -= 0.1f;
    updateTransform();
}

void Controller::moveRight()
{
    moveX += 0.1f;
    updateTransform();
}

void Controller::moveUp()
{
    moveY += 0.1f;
    updateTransform();
}

void Controller::moveDown()
{
    moveY -= 0.1f;
    updateTransform();
}

}
