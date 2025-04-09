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
    const auto rectangle = m_pixelBuffer->boundingBox();
    m_layer->addRectangle(rectangle, m_pixelBuffer->data().data());
    m_image->mergeRectangle(rectangle);
    m_image->mergedLayer()->update();
}

void PixelOperation::undo()
{
    const auto rectangle = m_pixelBuffer->boundingBox();

    m_layer->subtractRectangle(rectangle, m_pixelBuffer->data().data());
    m_image->mergeRectangle(rectangle);
    m_image->mergedLayer()->update();
}
}
