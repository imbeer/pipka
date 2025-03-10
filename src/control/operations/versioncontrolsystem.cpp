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

void VersionControlSystem::undo()
{
    if (m_doneOperationStack.empty())
        return;
    const auto operation= m_doneOperationStack.back();
    m_doneOperationStack.pop_back();
    m_unDoneOperationStack.push_back(operation);
    operation->undo();
}

void VersionControlSystem::redo()
{
    if (m_unDoneOperationStack.empty())
        return;
    const auto operation= m_unDoneOperationStack.back();
    m_unDoneOperationStack.pop_back();
    m_doneOperationStack.push_back(operation);
    operation->apply();
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


}