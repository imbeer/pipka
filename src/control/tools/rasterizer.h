#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <QVector3D>

#include "tool.h"

namespace PIPKA::CONTROL::TOOLS {

class Rasterizer : public Tool
{    
public:
    Rasterizer();

    void action(const QVector3D &currentPoint,
                const optional<QVector3D> &previousPoint,
                const LayerPtr &layer,
                const ImagePtr &image) override;

    void release() override;
    void confirm() override;

private:
    /// brazenham line rasterization
    void drawLine(
        LayerPtr layer,
        const QVector3D &start,
        const QVector3D &end);

    // float distanceToPreviousPoint(const QVector3D &first, const QVector3D &second);
    // bool isFarEnough(const QVector3D &first, const QVector3D &second);

    /// get new color according to blending and alpha channel.
    [[nodiscard]] Color calculateColor(
        LayerPtr layer,
        const Color &color,
        const int &x, const int &y,
        const double &startPressure, const double &endPressure,
        const float &interpolation) const;

private:
    // std::optional<QVector3D> m_previousPoint;
    Color m_color{0xFF00FFFF};
    std::shared_ptr<IMAGE::COLOR::Blend> m_blend;

};

}

#endif // RASTERIZER_H
