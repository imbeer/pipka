#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QMatrix3x3>
#include <QMatrix4x4>

#include "../../image/pixel-structure/image.h"

namespace PIPKA::CONTROL
{

class Transform : public QObject{
    Q_OBJECT
public:
    explicit Transform(const std::shared_ptr<IMAGE::Image> &image);

    void scaleUp();
    void scaleDown();
    void rotateLeft();
    void rotateRight();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void updateProjection(const float &viewPortRatio);
    void updateTransform();
    void updateFullMatrix();

signals:
    void updated();

public:
    QMatrix3x3 m_mvp;
    QMatrix3x3 m_i_mvp;

private:
    QMatrix3x3 m_transform;
    QMatrix3x3 m_i_transform;
    QMatrix3x3 m_projection;
    QMatrix3x3 m_i_projection;

private:
    std::shared_ptr<IMAGE::Image> m_image;
    float scaleX = 0.75f;
    float scaleY = 0.75f;
    float viewRatio = 1.0f;
    float angle = 0.0f;
    float moveX = 0.0f;
    float moveY = 0.0f;
};

}

#endif //TRANSFORM_H
