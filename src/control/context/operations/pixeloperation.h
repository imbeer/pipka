#ifndef PIXELOPERATION_H
#define PIXELOPERATION_H

#include "operation.h"
#include "../../../image/pixel-structure/buffer/temporarypixelbuffer.h"
#include "../../tools/tool.h"

namespace PIPKA::CONTROL::VERSIONCONTROL
{
class PixelOperation : public Operation{

public:
    explicit PixelOperation(
        IMAGE::ImagePtr image,
        const IMAGE::UnchunkedLayerPtr &layer);
    ~PixelOperation() override;
    void apply() override;
    void undo() override;
    void prepare() override;
    [[nodiscard]] IMAGE::UnchunkedLayerPtr layer() const {return m_layer;}
    [[nodiscard]] IMAGE::ImagePtr image() const {return m_image;}
    [[nodiscard]] std::shared_ptr<IMAGE::BUFFER::TemporaryPixelBuffer> pixels() const {return m_pixelBuffer;}
    [[nodiscard]] std::shared_ptr<IMAGE::BUFFER::LayerVersionBuffer> versions() const {return m_layer->versions();}

private:
    std::shared_ptr<IMAGE::BUFFER::TemporaryPixelBuffer> m_pixelBuffer;
    IMAGE::UnchunkedLayerPtr m_layer;
    IMAGE::ImagePtr m_image;

    // static std::map<IMAGE::UnchunkedLayer *, std::vector<PixelVersion>> m_imageVersions;
};
}
#endif //PIXELOPERATION_H
