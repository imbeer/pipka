#ifndef MOVETOOL_H
#define MOVETOOL_H
#include "tool.h"

namespace PIPKA::CONTROL::TOOLS {

class MoveTool final : public Tool {
public:
    explicit MoveTool(const VersionControlPtr &versionControlSystem);

    void action(
        const QVector3D &currentPoint,
        const optional<QVector3D> &previousPoint,
        const ImagePtr &image,
        const std::shared_ptr<Transform> &transform) override;
    void release() override;
    void confirm() override;

};

}
#endif //MOVETOOL_H
