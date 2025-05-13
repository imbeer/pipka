#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../image/pixel-structure/image.h"
#include "tools/tool.h"
#include <QImage>
#include <QObject>

#include "context/transform.h"
#include "context/operations/versioncontrolsystem.h"
#include "tools/brushes/brush.h"

namespace PIPKA::CONTROL {

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller();

    void createImage(const int &w, const int &h);
    void saveImage(const QString &path = "output.png") const;
    void clearActiveLayer() const;

    void handleClick(const double &x, const double &y, const double &pressure = 1);
    void handleRelease(const double &x, const double &y, const double &pressure = 1);
    void handleMove(const double &x, const double &y, const double &pressure = 1); /// mapped -1 to 1

    [[nodiscard]] QVector3D coordinates(const double &x, const double &y, const double &pressure = 1) const;
    [[nodiscard]] std::shared_ptr<Transform> transform() const {return m_transform;};
    IMAGE::ImagePtr image() {return m_image;};
    TOOLS::VersionControlPtr versionControl() {return m_versionControlSystem;}
signals:
    void updated();
    void imageCreated();

private:
    /// distance between points, where z is tablet pressure
    static float distance(const QVector3D &first, const QVector3D &second) { return
        pow(pow((first.x() - second.x()), 2)
            + pow((first.y() - second.y()), 2), 0.5);
    }

    static bool isFarEnough(const QVector3D &first, const QVector3D &second) { return distance(first, second) >= 1; }

private:
    IMAGE::ImagePtr m_image;
    std::shared_ptr<TOOLS::Tool> m_activeTool;
    std::shared_ptr<TOOLS::BRUSH::Brush> m_brush;
    std::shared_ptr<Transform> m_transform;
    TOOLS::VersionControlPtr m_versionControlSystem;

    bool m_pressed = false;
    std::optional<QVector3D> m_previousPoint;
};

}

#endif // CONTROLLER_H
