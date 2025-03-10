#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../image/image.h"
#include "tools/tool.h"
#include <QMatrix3x3>
#include <QMatrix4x4>
#include <QImage>

#include "operations/versioncontrolsystem.h"

namespace PIPKA::CONTROL {

class Controller
{
public:
    Controller();

    [[nodiscard]] QMatrix3x3 transform() const {return m_mvp;};
    std::shared_ptr<IMAGE::Image> getImage() {return m_image;};

    void setActiveLayerIndex(const int &index) {m_activeLayerIndex = index; qDebug() << index;};

    void createImage(const int &w, const int &h);
    void saveImage(const QString &path = "output.png") const;
    void clearActiveLayer() const;
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

    /// distance between points, where z is tablet pressure
    static float distance(const QVector3D &first, const QVector3D &second) { return
        std::pow(std::pow((first.x() - second.x()), 2)
            + std::pow((first.y() - second.y()), 2), 0.5);
    }

    static bool isFarEnough(const QVector3D &first, const QVector3D &second) { return distance(first, second) >= 1; }

    [[nodiscard]] bool isOutside(const QVector3D &point) const { return (
        point.x() < 0
        || point.y() < 0
        || point.x() >= m_image->width()
        || point.y() >= m_image->height());
    };

private:
    std::shared_ptr<IMAGE::Image> m_image;
    std::shared_ptr<TOOLS::Tool> m_tool;
    TOOLS::VersionControlPtr m_versionControlSystem;
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
