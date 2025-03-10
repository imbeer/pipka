#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <QVector3D>

#include "tool.h"
#include "../operations/pixeloperation.h"
#include "brushes/brush.h"

namespace PIPKA::CONTROL::TOOLS {

class Rasterizer final : public Tool
{    
public:
    explicit Rasterizer(const VersionControlPtr &versionControlSystem);

    void action(const QVector3D &currentPoint,
                const optional<QVector3D> &previousPoint,
                const LayerPtr &layer,
                const ImagePtr &image) override;

    void release() override;
    void confirm() override;

private:
    /// brazenham line rasterization
    void drawLine(
        const QVector3D &start,
        const QVector3D &end);

private:
    std::shared_ptr<BRUSH::Brush> m_brush;
    std::shared_ptr<VERSIONCONTROL::PixelOperation> m_operation;
};

}

#endif // RASTERIZER_H
