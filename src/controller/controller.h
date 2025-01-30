#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../image/image.h"
#include <QMatrix3x3>
#include <QMatrix4x4>

namespace PIPKA::CONTROL {

class Controller
{
public:
    Controller();
    void createImage(const int &w, const int &h);
    inline QMatrix3x3 transform() {return m_mvp;};
    inline std::optional<PIPKA::IMAGE::Image> getImage() {return m_image;};

    void scaleUp();
    void scaleDown();
    void rotateLeft();
    void rotateRight();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void handleClick(const double &x, const double &y); /// mapped -1 to 1

    void updateProjection(const float &viewPortRatio);

private:
    void updateTransform();
    void updateFullMatrix();

private:
    std::optional<PIPKA::IMAGE::Image> m_image; // todo something better idk
    QMatrix3x3 m_transform;
    QMatrix3x3 m_i_transform;

    QMatrix3x3 m_projection;
    QMatrix3x3 m_i_projection;

    QMatrix3x3 m_mvp;
    QMatrix3x3 m_i_mvp;

    float scaleX = 0.75f;
    float scaleY = 0.75f;
    float viewRatio = 1.0f;
    float angle = 0.0f;
    float moveX = 0.0f;
    float moveY = 0.0f;
};

}

#endif // CONTROLLER_H
