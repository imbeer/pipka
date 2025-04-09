#ifndef PIXELOPERATION_H
#define PIXELOPERATION_H

#include "operation.h"
#include "../../../image/pixel-structure/temporarypixelbuffer.h"
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
    std::shared_ptr<IMAGE::PIXELMAP::TemporaryPixelBuffer> getBuffer() const {return m_pixelBuffer;}

private:
    std::shared_ptr<IMAGE::PIXELMAP::TemporaryPixelBuffer> m_pixelBuffer;
    IMAGE::UnchunkedLayerPtr m_layer;
    IMAGE::ImagePtr m_image;
};
}
#endif //PIXELOPERATION_H
