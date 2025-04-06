#include "brushrepository.h"

#include "../tools/brushes/squarebrush.h"

namespace PIPKA::CONTROL::TOOLS
{

template<>
std::unique_ptr<BrushRepository> Repository<BrushRepository, BrushStorage>::m_instance = nullptr;

BrushRepository::BrushRepository()
{
    // todo: load brushes
    addBrush<BRUSH::SquareBrush>();
    addBrush<BRUSH::Brush>();
}

BrushRepository::~BrushRepository()
{
    // todo: serialize brushes
}

void BrushRepository::selectBrush(const int index)
{
    m_activeBrush = m_storage.at(index);
    emit brushSelected();
}

}
