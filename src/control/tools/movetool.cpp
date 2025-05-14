#include "movetool.h"

namespace PIPKA::CONTROL::TOOLS {

MoveTool::MoveTool(const VersionControlPtr &versionControlSystem) :
    Tool(versionControlSystem)
{ }

void MoveTool::action(
    const QVector3D &currentPoint,
    const optional<QVector3D> &previousPoint,
    const ImagePtr &image,
    const std::shared_ptr<Transform> &transform)
{
    if (transform == nullptr || !previousPoint.has_value()) {
        return;
    }

    const float deltaX = currentPoint.x() - previousPoint->x();
    const float deltaY = currentPoint.y() - previousPoint->y();

    transform->moveVector(deltaX, deltaY);
}

void MoveTool::release()
{
}

void MoveTool::confirm()
{
}

}
