#ifndef PIXELOPERATION_H
#define PIXELOPERATION_H

#include "operation.h"
#include "../../../image/pixel-structure/pixelmap.h"
#include "../../tools/tool.h"

namespace PIPKA::CONTROL::VERSIONCONTROL
{
class PixelOperation : public Operation{
public:
    explicit PixelOperation(
        const IMAGE::ImagePtr &image,
        const IMAGE::UnchunkedLayerPtr &layer);
    ~PixelOperation() override;
    void apply() override;
    void undo() override;
    IMAGE::UnchunkedLayerPtr getLayer() const {return m_layer;}
    std::shared_ptr<IMAGE::PIXELMAP::PixelMap> getMap() const {return m_colorDifferences;}

private:
    std::shared_ptr<IMAGE::PIXELMAP::PixelMap> m_colorDifferences;
    IMAGE::UnchunkedLayerPtr m_layer;
    IMAGE::ImagePtr m_image;
};
}
#endif //PIXELOPERATION_H
