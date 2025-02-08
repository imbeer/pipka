#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../image/image.h"
#include "tools/tool.h"
#include <QMatrix3x3>
#include <QMatrix4x4>
#include <QImage>

namespace PIPKA::CONTROL {

class Controller
{
public:
    Controller();
    inline QMatrix3x3 transform() {return m_mvp;};
    inline std::shared_ptr<PIPKA::IMAGE::Image> getImage() {return m_image;};

    void createImage(const int &w, const int &h);
    void saveImage(const QString &path = "output.png");
    void clearActiveLayer();
    void addLayer();

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
    /// distance between points, where z is tablet pressure
    inline float distance(const QVector3D &first, const QVector3D &second) { return
        std::pow(std::pow((first.x() - second.x()), 2)
                 + std::pow((first.y() - second.y()), 2), 0.5);
    }

    inline bool isFarEnough(const QVector3D &first, const QVector3D &second) { return distance(first, second) >= 1; }

    inline bool isOutside(const QVector3D &point) { return (
        point.x() < 0
        || point.y() < 0
        || point.x() >= m_image->width()
        || point.y() >= m_image->height());
    };

private:
    std::shared_ptr<PIPKA::IMAGE::Image> m_image;
    std::shared_ptr<TOOLS::Tool> m_tool;
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
    std::optional<QVector3D> m_previousPoint;

    int m_activeLayerIndex = 0;
};

}

#endif // CONTROLLER_H
