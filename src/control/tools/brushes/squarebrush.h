#ifndef SQUAREBRUSH_H
#define SQUAREBRUSH_H
#include "brush.h"

namespace PIPKA::CONTROL::TOOLS::BRUSH
{

class SquareBrush : public Brush
{
public:
    explicit SquareBrush(
        IMAGE::COLOR::Blend *blend,
        Color color = 0xFFFFFFFF);
    ~SquareBrush() override = default;
    void draw(
        std::shared_ptr<VERSIONCONTROL::PixelOperation> operation,
        int centerX, int centerY,
        float interpolation,
        float pressure,
        int deltaX, int deltaY) override;

    [[nodiscard]] Color calculateColors(
        const IMAGE::UnchunkedLayerPtr &layer,
        int x, int y,
        float interpolation,
        float pressure) override;

    QString name() const override {return "Square brush";}

};

}
#endif //SQUAREBRUSH_H
