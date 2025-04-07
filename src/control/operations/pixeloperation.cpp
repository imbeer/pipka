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
    for (const auto &[position, colorDifference] : m_colorDifferences->getMap()) {
        const int x = position.first;
        const int y = position.second;
        m_layer->addPixelColor(x, y, colorDifference);
    }
    m_layer->update();
}

void PixelOperation::undo()
{
    for (const auto &[position, colorDifference] : m_colorDifferences->getMap()) {
        const int x = position.first;
        const int y = position.second;
        m_layer->subtractPixelColor(x, y, colorDifference);
    }
    m_layer->update();
}
}
