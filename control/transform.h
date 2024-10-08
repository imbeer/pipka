#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QTransform>

namespace CONTROL
{

class Transform
{
public:
    Transform();
    ~Transform();
    void setScale(const float scale);
    void setRotate(const float rotate);
    void setTranslate(const float x, const float y);
    inline float scale() {return m_scale;};
    inline float rotate() {return m_rotate;};
    inline float x() {return m_x;};
    inline float y() {return m_y;};

private:
    QTransform m_transformMatrix;
    float m_scale;
    float m_rotate;
    float m_x;
    float m_y;

};

}

#endif // TRANSFORM_H
