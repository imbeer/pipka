#ifndef OPERATION_H
#define OPERATION_H


/// Base interface for operations in version control system
namespace PIPKA::CONTROL::VERSIONCONTROL
{
class Operation {

public:
    Operation() = default;
    virtual ~Operation() = default;
    virtual void apply() = 0;
    virtual void undo() = 0;

};
}

#endif //OPERATION_H
