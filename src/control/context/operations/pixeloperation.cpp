#include "pixeloperation.h"

namespace PIPKA::CONTROL::VERSIONCONTROL
{
PixelOperation::PixelOperation(
    const IMAGE::ImagePtr &image,
    const IMAGE::UnchunkedLayerPtr &layer)
    : Operation(), m_pixelBuffer(std::make_shared<IMAGE::PIXELMAP::TemporaryPixelBuffer>(layer->m_rect)), m_layer(layer), m_image(image)
{ }

PixelOperation::~PixelOperation()
{ }

void PixelOperation::apply()
{
    m_layer->addRectangle(m_pixelBuffer->boundingBox(), m_pixelBuffer->data().data());
    m_image->mergedLayer()->update();
}

void PixelOperation::undo()
{
    m_layer->subtractRectangle(m_pixelBuffer->boundingBox(), m_pixelBuffer->data().data());
    m_image->mergedLayer()->update();
}
}
