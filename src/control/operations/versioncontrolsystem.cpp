#include "versioncontrolsystem.h"

namespace PIPKA::CONTROL::VERSIONCONTROL
{
VersionControlSystem::VersionControlSystem()
= default;

VersionControlSystem::~VersionControlSystem()
{
    m_unDoneOperationStack.clear();
    m_doneOperationStack.clear();
}

void VersionControlSystem::addOperation(const std::shared_ptr<Operation> &operation)
{
    if (!m_unDoneOperationStack.empty()) {
        m_unDoneOperationStack.clear();
    }
    m_doneOperationStack.push_back(operation);
    if (m_doneOperationStack.size() > maxOperations) {
        m_doneOperationStack.pop_front();
    }
}

std::shared_ptr<Operation> VersionControlSystem::popOperation()
{
    if (m_doneOperationStack.empty())
        return nullptr;
    std::shared_ptr<Operation> result = m_doneOperationStack.back();
    m_doneOperationStack.pop_back();
    m_unDoneOperationStack.push_back(result);
    return result;
}
}