#include "transform.h"

namespace PIPKA::CONTROL
{

Transform::Transform(const IMAGE::ImagePtr &image) :
    QObject(nullptr),
    m_image(image)
{ }

void Transform::scaleUp()
{
    scaleX += 0.1f;
    scaleY += 0.1f;
    updateTransform();
}

void Transform::scaleDown()
{
    if (scaleX <= 0.01 && scaleY <= 0.01) return;
    scaleX -= 0.1f;
    scaleY -= 0.1f;
    updateTransform();
}

void Transform::rotateLeft()
{
    angle += M_PI / 36;
    if (angle > 2 * M_PI)
        angle -= 2 * M_PI;
    updateTransform();
}

void Transform::rotateRight()
{
    angle -= M_PI / 36;
    if (angle < -2 * M_PI)
        angle += 2 * M_PI;
    updateTransform();
}

void Transform::updateFullMatrix()
{
    m_mvp = m_projection * m_transform;
    m_i_mvp = m_i_transform * m_i_projection;
    emit updated();
}

void Transform::moveLeft()
{
    moveX -= 0.1f;
    updateTransform();
}

void Transform::moveRight()
{
    moveX += 0.1f;
    updateTransform();
}

void Transform::moveUp()
{
    moveY += 0.1f;
    updateTransform();
}

void Transform::moveDown()
{
    moveY -= 0.1f;
    updateTransform();
}

void Transform::moveToDeltaX(const float x)
{
    moveX += x;
    updateTransform();
}

void Transform::moveToDeltaY(const float y)
{
    moveY += y;
    updateTransform();
}

void Transform::moveVector(const float x, const float y)
{
    moveX += x;
    moveY += y;
    updateTransform();
}


void Transform::setImage(const IMAGE::ImagePtr &image)
{
    m_image = image;
    updateTransform();
}

void Transform::updateProjection(const float &viewportRatio)
{
    /// first row
    m_projection(0, 0) = 1 / viewportRatio;
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
    m_i_projection(0, 0) = viewportRatio;
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

void Transform::updateTransform()
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

}