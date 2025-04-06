#ifndef VERSIONCONTROLSYSTEM_H
#define VERSIONCONTROLSYSTEM_H

#include <memory>
#include <stack>

#include "operation.h"

namespace PIPKA::CONTROL::VERSIONCONTROL
{
class VersionControlSystem {
public:
    VersionControlSystem();
    ~VersionControlSystem();
    void undo();
    void redo();


    void addOperation(std::shared_ptr<Operation> operation);
private:
    const int maxOperations = 10;
    std::deque<std::shared_ptr<Operation>> m_doneOperationStack;
    std::deque<std::shared_ptr<Operation>> m_unDoneOperationStack;
};

using VersionControlPtr = std::shared_ptr<VERSIONCONTROL::VersionControlSystem>;

}

#endif //VERSIONCONTROLSYSTEM_H
