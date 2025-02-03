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
        clearPoint();
        return;
    }

    if (!m_previousPoint.has_value()) {
        m_previousPoint.emplace(std::move(point));
        int x = static_cast<int>(point.x());
        int y = static_cast<int>(point.y());
        layer->drawPixel(
            x, y,
            calculateColor(layer, m_color, x, y, point.z(), point.z(), 1));
        layer->update();
        return;
    }
    if (m_previousPoint->distanceToPoint(point) < 1) {
        qDebug() << "not redrawing";
        return;
    }

    drawLine(layer, *m_previousPoint, point);
    m_previousPoint.emplace(std::move(point));
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
    double startPressure = start.z();
    double endPressure = start.z();
    qDebug() << "start pressure" << startPressure;
    qDebug() << "end pressure" << endPressure;

    int deltaX = abs(endX - startX);
    int deltaY = abs(endY - startY);
    int stepX = (startX < endX) ? 1 : -1;
    int stepY = (startY < endY) ? 1 : -1;

    int errorTerm = deltaX - deltaY;
    int totalSteps = std::max(deltaX, deltaY);

    for (int currentStep = 0; currentStep <= totalSteps; ++currentStep) {
        float interpolation = (totalSteps != 0) ? (static_cast<float>(currentStep) / totalSteps) : 0.0f;
        layer->drawPixel(
            startX,
            startY,
            calculateColor(
                layer,
                m_color,
                startX, startY,
                startPressure, endPressure,
                interpolation));

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
    layer->update();
}

void Rasterizer::clearPoint()
{
    // qDebug() << "point list cleared";
    m_previousPoint.reset();
}

Color Rasterizer::calculateColor(
    const LayerPtr layer,
    const Color &color,
    const int &x, const int &y,
    const double &startPressure, const double &endPressure,
    const float &interpolation)
{
    qDebug() << "point interpolation" << interpolation;
    using namespace PIPKA::IMAGE;
    // todo: here should be a brush method or something, but for now
    const double pressure = std::clamp(interpolation * (endPressure - startPressure) + startPressure, 0.0, 1.0);
    qDebug() << "point pressure" << pressure;
    Color baseColor = layer->getColor(x, y);
    Color paintColor = color;
    auto alpha = getAlpha(paintColor);
    alpha *= pressure;
    setAlpha(paintColor, alpha);
    qDebug() << QString::number(paintColor, 16);
    const Color blendedColor = blendColors(paintColor, baseColor);
    qDebug() << QString::number(blendedColor, 16);
    return blendedColor;
}

}
