#include "toolrepository.h"

#include "../tools/movetool.h"
#include "../tools/rasterizer.h"

namespace PIPKA::CONTROL::TOOLS
{

template<>
std::unique_ptr<ToolRepository> Repository<ToolRepository, ToolStorage>::m_instance = nullptr;

ToolRepository::ToolRepository() :
    m_versionControl(std::make_shared<VERSIONCONTROL::VersionControlSystem>())
{
    add(std::make_unique<Rasterizer>(m_versionControl));
    add(std::make_unique<MoveTool>(m_versionControl));
    setActive<Rasterizer>();
}

ToolRepository::~ToolRepository()
{
}
}
