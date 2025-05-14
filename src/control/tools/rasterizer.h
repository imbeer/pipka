#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "tool.h"
#include "../context/operations/pixeloperation.h"

namespace PIPKA::CONTROL::TOOLS {

class Rasterizer final : public Tool
{    
public:
    explicit Rasterizer(
        const VersionControlPtr &versionControlSystem);

    void action(const QVector3D &currentPoint,
                const optional<QVector3D> &previousPoint,
                const ImagePtr &image,
                const std::shared_ptr<Transform> &transform) override;

    void release() override;
    void confirm() override;

private:
    /// brazenham line rasterization
    // todo: implement custom brute-force algorithm with float interval to allow antialiasing on brush level
    void drawLine(
        const QVector3D &start,
        const QVector3D &end);
    static void checkUpdatedChunks(
        const IMAGE::ChunkedLayerPtr &layer,
        const QVector3D &currentPoint);

private:
    std::shared_ptr<VERSIONCONTROL::PixelOperation> m_operation;
};

}

#endif // RASTERIZER_H
