#ifndef BRUSH_H
#define BRUSH_H
#include <memory>

#include "../tool.h"
#include "../../../image/color/blend.h"
#include "../../../image/color/color.h"
#include "../../context/operations/pixeloperation.h"

namespace PIPKA::CONTROL::TOOLS::BRUSH
{
class Brush {
public:
    explicit Brush(
        IMAGE::COLOR::Blend *blend,
        Color color = 0xFFFFFFFF);

    virtual ~Brush() = default;

    void setRadius(const int radius) { this->m_radius = radius; }
    void setInterval(const int interval) {this->drawCallInterval = interval; }
    void setColor(Color color);
    void setBlend(IMAGE::COLOR::Blend *blend);
    int drawInterval() const { return this->drawCallInterval; }
    int radius() const { return this->m_radius; }

    virtual void draw(
        std::shared_ptr<VERSIONCONTROL::PixelOperation> operation,
        int centerX, int centerY,
        float interpolation,
        float pressure,
        int deltaX, int deltaY);

    [[nodiscard]] virtual Color calculateColors(
        const IMAGE::UnchunkedLayerPtr &layer,
        int x, int y,
        float interpolation, float pressure);

protected:
    IMAGE::COLOR::Blend *m_blend;
    /// Half of bounding square side where changes of layer were made.
    /// Will be useful to update only a part of texture later.
    int m_radius = 1;
    /// Interval in steps (pixels) between brush calls during line.
    /// Use it for
    int drawCallInterval = 0;
    Color m_color = 0xFFFFFFFF;
};

}

#endif //BRUSH_H
