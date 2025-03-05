#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <QVector3D>

#include "tool.h"
#include "brushes/Brush.h"

namespace PIPKA::CONTROL::TOOLS {

class Rasterizer final : public Tool
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
        const LayerPtr &layer,
        const QVector3D &start,
        const QVector3D &end);

private:
    // std::optional<QVector3D> m_previousPoint;
    // Color m_color{0xFF00FFFF};
    // std::shared_ptr<IMAGE::COLOR::Blend> m_blend;
    std::shared_ptr<BRUSH::Brush> m_brush;
};

}

#endif // RASTERIZER_H
