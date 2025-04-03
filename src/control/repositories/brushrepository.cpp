#include "brushrepository.h"

#include "blendrepository.h"

namespace PIPKA::CONTROL::TOOLS
{

/// some magic
// todo: wtf is going on
template<>
std::unique_ptr<BrushRepository> Repository<BrushRepository, BrushStorage>::m_instance = nullptr;

BrushRepository::BrushRepository()
{
    // todo: load brushes
    addBrush();
}

BrushRepository::~BrushRepository()
{
    // todo: serialize brushes
}

void BrushRepository::addBrush()
{
    const auto newBrush = std::make_shared<BRUSH::Brush>(
        BlendRepository::instance()->getBlend<IMAGE::COLOR::NormalBlend>(),
        0xFFFFFFFF);
    m_storage.push_back(newBrush);
    selectBrush(m_storage.size() - 1);
}

void BrushRepository::selectBrush(const int index)
{
    m_activeBrush = m_storage.at(index);
    emit brushSelected();
}

}
