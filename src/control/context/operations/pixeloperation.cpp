#include "pixeloperation.h"

#include <utility>

namespace PIPKA::CONTROL::VERSIONCONTROL
{
PixelOperation::PixelOperation(
    IMAGE::ImagePtr image,
    const IMAGE::UnchunkedLayerPtr &layer)
    : Operation(), m_pixelBuffer(std::make_shared<IMAGE::BUFFER::TemporaryPixelBuffer>(layer->m_rect)), m_layer(layer), m_image(std::move(image))
{
    m_layer->versions()->incrementTotalVersion();
}

PixelOperation::~PixelOperation()
= default;

void PixelOperation::apply()
{
    // m_layer->versions()->incrementTotalVersion();
    for (auto &[position, color] : m_pixelBuffer->pixels()) {
        m_image->addPixelColor(position.first, position.second, color, m_layer);
        // m_image->mergePixel(position.first, position.second);
    }
    // const auto rectangle = m_pixelBuffer->boundingBox();
    // m_layer->addRectangle(rectangle, m_pixelBuffer->data().data());
    // m_image->mergeRectangle(rectangle);
    m_image->mergedLayer()->update();
}

void PixelOperation::undo()
{
    // m_layer->versions()->incrementTotalVersion();
    for (auto &[position, color] : m_pixelBuffer->pixels()) {
        m_image->subtractPixelColor(position.first, position.second, color, m_layer);
        // m_image->mergePixel(position.first, position.second);
    }
    // const auto rectangle = m_pixelBuffer->boundingBox();
    // m_layer->subtractRectangle(rectangle, m_pixelBuffer->data().data());
    // m_image->mergeRectangle(rectangle);
    m_image->mergedLayer()->update();
}

void PixelOperation::prepare()
{
    m_layer->versions()->incrementTotalVersion();
    m_pixelBuffer->clearPixelBuffer();
}
}
