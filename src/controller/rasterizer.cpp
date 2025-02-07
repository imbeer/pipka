#include "rasterizer.h"
#include <qdebug.h>
#include <qimage.h>

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

    if (!isFarEnough(point)) {
        qDebug() << "not redrawing";
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

    for (int currentStep = 1; currentStep <= totalSteps; ++currentStep) {
        float interpolation = static_cast<float>(currentStep) / totalSteps;
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

QImage Rasterizer::renderImage(const std::shared_ptr<PIPKA::IMAGE::Image> image)
{
    const int w = image->width();
    const int h = image->height();
    std::vector<Color> buffer(w * h, 0x00);

    auto start = std::chrono::high_resolution_clock::now();

    for (int pixelInd = 0; pixelInd < w * h; ++pixelInd) {
        Color baseColor = 0x00;
        for (const auto &layer : image->layers()) {
            baseColor = IMAGE::blend(baseColor, layer->getColor(pixelInd), IMAGE::BlendMode::NORMAL);
        }
        buffer.at(pixelInd) = baseColor;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    qDebug() << duration.count();


    return QImage(
        reinterpret_cast<const uchar*>(buffer.data()),
        w, h,
        w * sizeof(Color), // Bytes per line
        QImage::Format_ARGB32);
}

void Rasterizer::clearPoint()
{
    // qDebug() << "point list cleared";
    m_previousPoint.reset();
}

float Rasterizer::distanceToPreviousPoint(const QVector3D &point)
{
    return std::pow(std::pow((point.x() - m_previousPoint->x()), 2)
                 + std::pow((point.y() - m_previousPoint->y()), 2), 0.5);
}

bool Rasterizer::isFarEnough(const QVector3D &point)
{
    return distanceToPreviousPoint(point) >= 1;
}

Color Rasterizer::calculateColor(
    const LayerPtr layer,
    const Color &color,
    const int &x, const int &y,
    const double &startPressure, const double &endPressure,
    const float &interpolation)
{
    using namespace PIPKA::IMAGE;
    // todo: here should be a brush method or something, but for now
    const double pressure = std::clamp(interpolation * (endPressure - startPressure) + startPressure, 0.0, 1.0);

    Color baseColor = layer->getColor(x, y);
    Color paintColor = color;

    auto alpha = COLOR::alpha(paintColor);
    alpha *= pressure;
    COLOR::setAlpha(paintColor, alpha);

    return blend(baseColor, paintColor, BlendMode::NORMAL);
}

}
