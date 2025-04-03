#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../image/image.h"
#include "tools/tool.h"
#include <QImage>

#include "transform.h"
#include "operations/versioncontrolsystem.h"
#include "tools/brushes/brush.h"

namespace PIPKA::CONTROL {
// todo: add brush repository and set color;
class Controller
{
public:
    Controller();

    [[nodiscard]] std::shared_ptr<Transform> transform() const {return m_transform;};
    std::shared_ptr<IMAGE::Image> getImage() {return m_image;};

    void setActiveLayerIndex(const int &index) {m_activeLayerIndex = index; qDebug() << index;};
    void setColor(IMAGE::Color color) const;

    void createImage(const int &w, const int &h);
    void saveImage(const QString &path = "output.png") const;
    void clearActiveLayer() const;
    void addLayer();

    void handleClick(const double &x, const double &y, const double &pressure = 1);
    void handleRelease(const double &x, const double &y, const double &pressure = 1);
    void handleMove(const double &x, const double &y, const double &pressure = 1); /// mapped -1 to 1

    [[nodiscard]] QVector3D getCoordinates(const double &x, const double &y, const double &pressure = 1) const;

    void undo() const;
    void redo() const;

private:
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
    std::shared_ptr<TOOLS::Tool> m_activeTool;
    std::shared_ptr<TOOLS::BRUSH::Brush> m_brush;
    std::shared_ptr<Transform> m_transform;
    TOOLS::VersionControlPtr m_versionControlSystem;


    bool m_pressed = false;
    std::optional<QVector3D> m_previousPoint;

    int m_activeLayerIndex = 0;
};

}

#endif // CONTROLLER_H
