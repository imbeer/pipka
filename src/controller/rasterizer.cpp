#include "rasterizer.h"
#include <qdebug.h>

namespace PIPKA::CONTROL {

Rasterizer::Rasterizer() {}

void Rasterizer::drawPoint(const LayerPtr layer, const QVector3D &point)
{
    // qDebug() << m_points.at(0);
    // qDebug() << m_points.size();

    if (point.x() < 0
        || point.y() < 0
        || point.x() >= layer->width()
        || point.y() >= layer->height()) {
        // qDebug() << "out of range";
        clearPointList();
        return;
    }

    if (m_points.empty()) {
        m_points.push_back(point);
        int x = static_cast<int>(point.x());
        int y = static_cast<int>(point.y());
        layer->drawPixel(
            x, y,
            calculateColor(layer, m_color, x, y, 1));
        return;
    }
    auto prevPoint = m_points.at(m_points.size() - 1);
    drawLine(layer, prevPoint, point);
    m_points.push_back(point);
    m_points.erase(m_points.begin());
}

void Rasterizer::drawLine(
    const LayerPtr layer,
    const QVector3D &start,
    const QVector3D &end)
{
    int startX = static_cast<int>(round(start.x()));
    int startY = static_cast<int>(round(start.y()));
    int endX = static_cast<int>(round(end.x()));
    int endY = static_cast<int>(round(end.y()));

    int deltaX = abs(endX - startX);
    int deltaY = abs(endY - startY);
    int stepX = (startX < endX) ? 1 : -1;
    int stepY = (startY < endY) ? 1 : -1;

    int errorTerm = deltaX - deltaY;
    int totalSteps = std::max(deltaX, deltaY);

    for (int currentStep = 0; currentStep <= totalSteps; ++currentStep) {
        float interpolationCoefficient = (totalSteps != 0) ? (static_cast<float>(currentStep) / totalSteps) : 0.0f;
        layer->drawPixel(startX, startY, calculateColor(layer, m_color, startX, startY, interpolationCoefficient));

        if (startX == endX && startY == endY) break;

        int doubleErrorTerm = 2 * errorTerm;
        if (doubleErrorTerm > -deltaY) {
            errorTerm -= deltaY;
            startX += stepX;
        }
        if (doubleErrorTerm < deltaX) {
            errorTerm += deltaX;
            startY += stepY;
        }
    }
}

void Rasterizer::clearPointList()
{
    // qDebug() << "point list cleared";
    m_points.clear();
}

Color Rasterizer::calculateColor(
    const LayerPtr layer,
    const Color &color,
    const int &x, const int &y,
    const float &interpolation)
{
    return color; // placeholder
}

}
