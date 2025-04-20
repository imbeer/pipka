#include "pixeloperation.h"

namespace PIPKA::CONTROL::VERSIONCONTROL
{
PixelOperation::PixelOperation(
    const IMAGE::ImagePtr &image,
    const IMAGE::UnchunkedLayerPtr &layer)
    : Operation(), m_pixelBuffer(std::make_shared<IMAGE::BUFFER::TemporaryPixelBuffer>(layer->m_rect)), m_layer(layer), m_image(image)
{
    layer->versions()->incrementVersion();
}

PixelOperation::~PixelOperation()
{ }

void PixelOperation::apply()
{
    for (auto &[position, color] : m_pixelBuffer->pixels()) {
        m_layer->addPixelColor(position.first, position.second, color);
        m_image->mergePixel(position.first, position.second);
    }
    // const auto rectangle = m_pixelBuffer->boundingBox();
    // m_layer->addRectangle(rectangle, m_pixelBuffer->data().data());
    // m_image->mergeRectangle(rectangle);
    m_image->mergedLayer()->update();
}

void PixelOperation::undo()
{
    for (auto &[position, color] : m_pixelBuffer->pixels()) {
        m_layer->subtractPixelColor(position.first, position.second, color);
        m_image->mergePixel(position.first, position.second);
    }
    // const auto rectangle = m_pixelBuffer->boundingBox();
    // m_layer->subtractRectangle(rectangle, m_pixelBuffer->data().data());
    // m_image->mergeRectangle(rectangle);
    m_image->mergedLayer()->update();
}

void PixelOperation::prepare()
{
    m_pixelBuffer->clearPixelBuffer();
}
}
