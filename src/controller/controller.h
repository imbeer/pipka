#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../image/image.h"
#include "rasterizer.h"
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

    void clearActiveLayer();

    void scaleUp();
    void scaleDown();
    void rotateLeft();
    void rotateRight();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void handleClick(const double &x, const double &y, const double &pressure = 1);
    void handleRelease(const double &x, const double &y, const double &pressure = 1);
    void handleMove(const double &x, const double &y, const double &pressure = 1); /// mapped -1 to 1

    QVector3D getCoordinates(const double &x, const double &y, const double &pressure = 1);

    void updateProjection(const float &viewPortRatio);

private:
    void updateTransform();
    void updateFullMatrix();

private:
    std::optional<PIPKA::IMAGE::Image> m_image; // todo something better idk
    Rasterizer m_rasterizer;
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

    bool m_pressed = false;

    int m_activeLayerIndex = 0;
};

}

#endif // CONTROLLER_H
