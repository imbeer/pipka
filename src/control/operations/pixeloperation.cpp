#include "pixeloperation.h"

namespace PIPKA::CONTROL::VERSIONCONTROL
{
PixelOperation::PixelOperation(const TOOLS::LayerPtr &layer)
    : Operation(), m_colorDifferences(std::make_shared<IMAGE::PIXELMAP::PixelMap>()), m_layer(layer)
{ }

PixelOperation::~PixelOperation()
{ }

void PixelOperation::apply()
{
    for (const auto &entry: m_colorDifferences->getMap()) {
        const int x = entry.first.first;
        const int y = entry.first.second;
        const IMAGE::Color colorDifference = entry.second;
        m_layer->addPixelColor(x, y, colorDifference);
    }
    m_layer->update(); //  m_colorDifferences->getBoundingBox()
}

void PixelOperation::undo()
{
    for (const auto &entry: m_colorDifferences->getMap()) {
        const int x = entry.first.first;
        const int y = entry.first.second;
        const IMAGE::Color colorDifference = entry.second;
        m_layer->subtractPixelColor(x, y, colorDifference);
    }
    m_layer->update(); // m_colorDifferences->getBoundingBox()
}
}
