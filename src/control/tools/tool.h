#ifndef TOOL_H
#define TOOL_H

#include <QVector3D>
#include "../../image/layer.h"
#include "../../image/image.h"

namespace PIPKA::CONTROL::TOOLS {

using std::optional, IMAGE::Color, IMAGE::Layer, IMAGE::Image;
using LayerPtr = std::shared_ptr<Layer>;
using ImagePtr = std::shared_ptr<Image>;


/// interface for all tools
class Tool
{
protected:
    ~Tool() = default;

public:
    // Tool();

public:
    /// happens every frame when mouse moved and when mouse pressed.
    /// example: if raster -> new line.
    /// params:
    /// QVector3D = (x, y, pressure)
    /// if there are no previous point, must start a new action.
    virtual void action(
        const QVector3D &currentPoint,
        const optional<QVector3D> &previousPoint,
        const LayerPtr &layer,
        const ImagePtr &image) = 0;

    /// finalizes action when mouse relises.
    /// example: select a part of layer, add a point in polygon
    virtual void release() = 0;

    /// if tool needs pressing a button for confirmation
    /// exmple: transform, spline or merge selection
    virtual void confirm() = 0;
};

}

#endif // TOOL_H
