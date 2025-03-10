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
    void addOperation(const std::shared_ptr<Operation> &operation);
    std::shared_ptr<Operation> popOperation();
private:
    const int maxOperations = 10;
    std::deque<std::shared_ptr<Operation>> m_doneOperationStack;
    std::deque<std::shared_ptr<Operation>> m_unDoneOperationStack;
};
}

#endif //VERSIONCONTROLSYSTEM_H
