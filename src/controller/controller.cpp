#include "controller.h"
#include <qdebug.h>

namespace PIPKA::CONTROL {

Controller::Controller()
    : m_image(std::nullopt)
{
    updateTransform();
    updateProjection(1);
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
    scaleX += 0.01f;
    scaleY += 0.01f;
    updateTransform();
}

void Controller::scaleDown()
{
    if (scaleX <= 0.01 && scaleY <= 0.01) return;
    scaleX -= 0.01f;
    scaleY -= 0.01f;
    updateTransform();
}

void Controller::rotateLeft()
{
    angle += M_PI / 36;
    if (angle > 2 * M_PI)
        angle -= 2 * M_PI;
    updateTransform();
}

void Controller::rotateRight()
{
    angle -= M_PI / 36;
    if (angle < -2 * M_PI)
        angle += 2 * M_PI;
    updateTransform();
}

void Controller::updateProjection(const float &viewPortRatio)
{
    if (!m_image.has_value()) return;
    qDebug() << viewPortRatio;
    m_projection(0, 0) = 1 / viewPortRatio;  m_projection(0, 1) = 0.0f;   m_projection(0, 2) = 0.0f;
    m_projection(1, 0) = 0.0f;  m_projection(1, 1) = 1.0f;  m_projection(1, 2) = 0.0f;
    m_projection(2, 0) = 0.0f;  m_projection(2, 1) = 0.0f;  m_projection(2, 2) = 1.0f;
    updateFullMatrix();

    qDebug() << m_projection;
    qDebug() << m_fullMatrix;
}


void Controller::updateTransform()
{
    const float imageRatio = m_image->ratio();
    // qDebug() << imageRatio;
    m_transform(0, 0) = scaleX * imageRatio * cos(angle);  m_transform(0, 1) = -scaleY * sin(angle);   m_transform(0, 2) = moveX;
    m_transform(1, 0) = scaleX * imageRatio * sin(angle);  m_transform(1, 1) = scaleY * cos(angle);    m_transform(1, 2) = moveY;
    m_transform(2, 0) = 0.0f;                 m_transform(2, 1) = 0.0f;                   m_transform(2, 2) = 1.0f;
    updateFullMatrix();
}

void Controller::updateFullMatrix()
{
    m_fullMatrix = m_projection * m_transform;
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
