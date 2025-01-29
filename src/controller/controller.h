#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../image/image.h"
#include <QMatrix3x3>

namespace PIPKA::CONTROL {

class Controller
{
public:
    Controller();
    void createImage(const int &w, const int &h);
    inline QMatrix3x3 transform() {return m_transform;};
    inline std::optional<PIPKA::IMAGE::Image> getImage() {return m_image;};
    void scaleUp();
    void scaleDown();
    void rotateLeft();
    void rotateRight();

private:
    void updateTransform();

private:
    std::optional<PIPKA::IMAGE::Image> m_image; // todo something better idk
    QMatrix3x3 m_transform;

    float scaleX = 0.0f;
    float scaleY = 0.0f;
    float angle = 0.0f;
    float moveX = 0.0f;
    float moveY = 0.0f;
};

}

#endif // CONTROLLER_H
