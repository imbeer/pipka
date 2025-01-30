#include "controller.h"
#include <qdebug.h>
#include <qvectornd.h>

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

void Controller::handleClick(const double &x, const double &y)
{
    const float normalizedX = x * m_i_mvp(0, 0) + y * m_i_mvp(0, 1) - 1 * m_i_mvp(0, 2);
    const float normalizedY = x * m_i_mvp(1, 0) + y * m_i_mvp(1, 1) + 1 * m_i_mvp(1, 2);

    // qDebug() << normalizedX;
    // qDebug() << normalizedY;

    float imageX = (1 - normalizedX) * m_image->width() * 0.5f;
    float imageY = (normalizedY + 1) * m_image->height() * 0.5f;

    // qDebug() << imageX;
    // qDebug() << imageY;

    if ((imageX < 0 || imageX >= m_image->width())
        || (imageY < 0 || imageY >= m_image->height()))
        return;

    m_image->layers()[m_activeLayerIndex]->drawPixel(imageX, imageY, 0xFFFFFFFF);
}

void Controller::updateProjection(const float &viewPortRatio)
{
    viewRatio = viewPortRatio;

    /// first row
    m_projection(0, 0) = 1 / viewPortRatio;
    m_projection(0, 1) = 0.0f;
    m_projection(0, 2) = 0.0f;
    /// second row
    m_projection(1, 0) = 0.0f;
    m_projection(1, 1) = 1.0f;
    m_projection(1, 2) = 0.0f;
    /// third row
    m_projection(2, 0) = 0.0f;
    m_projection(2, 1) = 0.0f;
    m_projection(2, 2) = 1.0f;

    /// first row
    m_i_projection(0, 0) = viewPortRatio;
    m_i_projection(0, 1) = 0.0f;
    m_i_projection(0, 2) = 0.0f;
    /// second row
    m_i_projection(1, 0) = 0.0f;
    m_i_projection(1, 1) = 1.0f;
    m_i_projection(1, 2) = 0.0f;
    /// third row
    m_i_projection(2, 0) = 0.0f;
    m_i_projection(2, 1) = 0.0f;
    m_i_projection(2, 2) = 1.0f;

    updateFullMatrix();
}


void Controller::updateTransform()
{
    const float imageRatio = m_image->ratio();
    /// first row
    m_transform(0, 0) = scaleX * imageRatio * cos(angle);
    m_transform(0, 1) = -scaleY * sin(angle);
    m_transform(0, 2) = moveX;
    /// second row
    m_transform(1, 0) = scaleX * imageRatio * sin(angle);
    m_transform(1, 1) = scaleY * cos(angle);
    m_transform(1, 2) = moveY;
    /// third row
    m_transform(2, 0) = 0.0f;
    m_transform(2, 1) = 0.0f;
    m_transform(2, 2) = 1.0f;

    /// first row
    m_i_transform(0, 0) = -cos(angle) / (scaleX * imageRatio);
    m_i_transform(0, 1) = -sin(angle) / (scaleX * imageRatio);
    m_i_transform(0, 2) = (-moveX * cos(angle) - moveY * sin(angle)) / (scaleX * imageRatio);
    /// second row
    m_i_transform(1, 0) = -sin(angle) / scaleY;
    m_i_transform(1, 1) =  cos(angle) / scaleY ;
    m_i_transform(1, 2) = (-moveY * cos(angle) + moveX * sin(angle)) / scaleY;
    /// third row
    m_i_transform(2, 0) = 0.0f;
    m_i_transform(2, 1) = 0.0f;
    m_i_transform(2, 2) = 1.0f;

    updateFullMatrix();
}

void Controller::updateFullMatrix()
{
    m_mvp = m_projection * m_transform;
    m_i_mvp = m_i_transform * m_i_projection;
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
