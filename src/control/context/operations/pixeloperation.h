#ifndef PIXELOPERATION_H
#define PIXELOPERATION_H

#include "operation.h"
#include "../../../image/pixel-structures/pixelmap.h"
#include "../../tools/tool.h"

namespace PIPKA::CONTROL::VERSIONCONTROL
{
class PixelOperation : public Operation{
public:
    explicit PixelOperation(const TOOLS::LayerPtr &layer);
    ~PixelOperation() override;
    void apply() override;
    void undo() override;
    TOOLS::LayerPtr getLayer() const {return m_layer;}
    std::shared_ptr<IMAGE::PIXELMAP::PixelMap> getMap() const {return m_colorDifferences;}

private:
    std::shared_ptr<IMAGE::PIXELMAP::PixelMap> m_colorDifferences;
    TOOLS::LayerPtr m_layer;
};
}
#endif //PIXELOPERATION_H
