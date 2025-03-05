#ifndef BRUSH_H
#define BRUSH_H
#include <memory>

#include "../tool.h"
#include "../../../image/color/blend.h"
#include "../../../image/color/color.h"

namespace PIPKA::CONTROL::TOOLS::BRUSH
{
class Brush {

public:
    explicit Brush(
        const std::shared_ptr<IMAGE::COLOR::Blend> &blend,
        Color color = 0xFFFFFFFF);

    virtual ~Brush() = default;

    virtual void draw(
        const LayerPtr &layer,
        int centerX, int centerY,
        float interpolation,
        float pressure,
        int deltaX, int deltaY);

    [[nodiscard]] virtual Color getColor(
        const LayerPtr &layer,
        int x, int y,
        float interpolation, float pressure);

private:
    std::shared_ptr<IMAGE::COLOR::Blend> blend;
    /// Half of bounding square side where changes of layer were made.
    /// Will be useful to update only a part of texture later.
    int radius;
    /// Interval in steps (pixels) between brush calls during line.
    /// Use it for
    int drawCallInterval;
    Color color;
};

}

#endif //BRUSH_H
