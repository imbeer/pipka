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
    const int maxOperations = 30;
    std::deque<std::shared_ptr<Operation>> m_doneOperationStack;
    std::deque<std::shared_ptr<Operation>> m_unDoneOperationStack;
};

using VersionControlPtr = std::shared_ptr<VersionControlSystem>;

}

#endif //VERSIONCONTROLSYSTEM_H
