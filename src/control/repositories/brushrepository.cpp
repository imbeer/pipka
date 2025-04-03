#include "brushrepository.h"

namespace PIPKA::CONTROL::TOOLS
{

/// some magic
// todo: wtf is going on
template<>
std::unique_ptr<BrushRepository> Repository<BrushRepository>::m_instance = nullptr;

BrushRepository::BrushRepository()
{
    // todo: load brushes
    addBrush();
}

BrushRepository::~BrushRepository()
{
    // todo: save brushes
}

void BrushRepository::addBrush()
{
    const auto newBrush = std::make_shared<BRUSH::Brush>(std::make_shared<IMAGE::COLOR::NormalBlend>(), 0xFFFFFFFF);
    m_brushes.push_back(newBrush);
    selectBrush(m_brushes.size() - 1);
}

void BrushRepository::setColor(const Color color) const
{
    assert(m_activeBrush != nullptr);
    m_activeBrush->setColor(color);
}

void BrushRepository::selectBrush(const int index)
{
    m_activeBrush = m_brushes.at(index);
    emit brushSelected();
}

}
