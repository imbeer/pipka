#ifndef TOOLREPOSITORY_H
#define TOOLREPOSITORY_H
#include <typeindex>

#include "repository.h"
#include "../tools/tool.h"

namespace PIPKA::CONTROL::TOOLS
{

using ToolStorage = std::map<std::type_index, std::unique_ptr<Tool>>;

// todo: maybe not?
class ToolRepository : public Repository<ToolRepository, ToolStorage>
{
    Q_OBJECT
public:
    explicit ToolRepository();
    ~ToolRepository() override;

    template<class ToolType>
    Tool *get() const
    {
        return m_storage.at(std::type_index(typeid(ToolType))).get();
    }

    template<class ToolType>
    void setActive()
    {
        m_activeTool = m_storage.at(std::type_index(typeid(ToolType))).get();
    }

    Tool *activeTool() const
    {
        return m_activeTool;
    }

    VersionControlPtr versionControl() const { return m_versionControl; }

private:
    template<class ToolType>
    void add(std::unique_ptr<ToolType> obj)
    {
        m_storage[std::type_index(typeid(ToolType))] = std::move(obj);
    }

private:
    VersionControlPtr m_versionControl;
    Tool *m_activeTool;
};

}
#endif //TOOLREPOSITORY_H
