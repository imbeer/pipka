#include "toolrepository.h"

#include "../tools/rasterizer.h"

namespace PIPKA::CONTROL::TOOLS
{

template<>
std::unique_ptr<ToolRepository> Repository<ToolRepository, ToolStorage>::m_instance = nullptr;

ToolRepository::ToolRepository(VersionControlPtr versionControl) :
    m_versionControl(versionControl)
{
    add(std::make_unique<Rasterizer>(versionControl));
}

ToolRepository::~ToolRepository()
{
}
}
