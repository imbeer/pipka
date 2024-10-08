#include "transform.h"

namespace CONTROL
{

Transform::Transform() {}

Transform::~Transform() {}

void Transform::setScale(const float scale)
{
    m_scale = scale;
    m_transformMatrix.scale(m_scale, m_scale);
}

void Transform::setRotate(const float rotate)
{
    m_rotate = rotate;
    m_transformMatrix.rotate(m_rotate);
}

void Transform::setTranslate(const float x, const float y)
{
    m_x = x;
    m_y = y;
    m_transformMatrix.translate(m_x, m_y);
}

}
