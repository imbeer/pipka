#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <QVector3D>
#include "../image/layer.h"

namespace PIPKA::CONTROL {

using Color = IMAGE::Color;
using Layer = IMAGE::Layer;
using LayerPtr = std::shared_ptr<Layer>;

class Rasterizer
{    
public:
    Rasterizer();

    void drawPoint(const LayerPtr layer, const QVector3D &point);
    /// brazenham
    void drawLine(
        const LayerPtr layer,
        const QVector3D &start,
        const QVector3D &end);
    void clearPoint();
    float distanceToPreviousPoint(const QVector3D &point);
    bool isFarEnough(const QVector3D &point);
    // void setColor(const Color &color);
    // inline const Color getColor() {return m_color;};

private:
    /// get new color according to blending and alpha channel.
    /// maybe should be moved to PIPKA::IMAGE::Layer.
    Color calculateColor(
        const LayerPtr layer,
        const Color &color,
        const int &x, const int &y,
        const double &startPressure, const double &endPressure,
        const float &interpolation);

private:
    // std::vector<QVector3D> m_points; /// x, y, pressure
    std::optional<QVector3D> m_previousPoint;
    Color m_color{0xFF00FFFF};

};

}

#endif // RASTERIZER_H
