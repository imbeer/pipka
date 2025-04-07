#include "canvaswidget.h"

#include <QOpenGLPixelTransferOptions>

namespace PIPKA::UI {

CanvasWidget::CanvasWidget(
    const std::shared_ptr<CONTROL::Controller> &controller,
    EventHandler *eventHandler,
    QWidget *parent) :
    QOpenGLWidget(parent), m_controller(controller),
    m_shaderProgram(nullptr), m_eventHandler(eventHandler)
{
    connect(
        m_controller->transform().get(),
        &CONTROL::Transform::updated,
        this,
        &CanvasWidget::callUpdate);
}

CanvasWidget::~CanvasWidget()
{
    for (const auto &textureRow : m_textures) {
        for (const auto &texture : textureRow) {
            texture->destroy();
        }
    }
    if (m_shaderProgram) {
        delete m_shaderProgram;
        m_shaderProgram = nullptr;
    }
}

void CanvasWidget::initializeTextures()
{
    const auto image = m_controller->image();

    for (const auto &chunkRow : m_controller->image()->mergedLayer()->chunks()) {
        auto textureRow = std::vector<std::shared_ptr<QOpenGLTexture>>();
        for (const auto &chunk : chunkRow) {
            auto texture = std::make_shared<QOpenGLTexture>(QOpenGLTexture::Target2D);

            texture->setSize(chunk->rect.w, chunk->rect.h);
            texture->setFormat(QOpenGLTexture::RGBA8_UNorm);
            texture->allocateStorage();
            texture->setMinMagFilters(
                QOpenGLTexture::Filter::Nearest,
                QOpenGLTexture::Filter::Nearest);
            texture->setData(
                QOpenGLTexture::BGRA,
                QOpenGLTexture::UInt8,
                chunk->data());

            textureRow.push_back(texture);
            // connect(chunk.get(), &IMAGE::Chunk::updated, this, &CanvasWidget::updateTextureData);

        }
        m_textures.push_back(textureRow);
    }
    connectTextures();
}

void CanvasWidget::updateTextureData(const int xInd, const int yInd)
{
    const auto layer = m_controller->image()->mergedLayer();
    const auto texture = m_textures.at(yInd).at(xInd);
    // qDebug() << "called updateTextureData on:" << xInd << yInd;
    texture->setData(
        QOpenGLTexture::BGRA,
        QOpenGLTexture::UInt8,
        layer->getChunk(xInd, yInd)->data());
    update();
}

void CanvasWidget::connectTextures()
{
    const int chunksByX = m_controller->image()->mergedLayer()->chunks().at(0).size();
    const int chunksByY = m_controller->image()->mergedLayer()->chunks().size();

    for (int yInd = 0; yInd < chunksByY; ++yInd) {
        for (int xInd = 0; xInd < chunksByX; ++xInd) {
            connect(
                m_controller->image()->mergedLayer()->getChunk(xInd, yInd).get(),
                &IMAGE::Chunk::updated,
                this,
                &CanvasWidget::updateTextureData);
        }
    }
}

void CanvasWidget::initializeGL()
{
    initializeOpenGLFunctions();
    initializeTextures();

    m_shaderProgram = new QOpenGLShaderProgram();
    m_shaderProgram->addShaderFromSourceFile(
        QOpenGLShader::Vertex,
        ":/canvas_vertex_shader.vert");
    m_shaderProgram->addShaderFromSourceFile(
        QOpenGLShader::Fragment,
        ":/canvas_fragment_shader.frag");
    m_shaderProgram->link();

    static const GLuint indices[] = {
        0, 1, 2,
        1, 2, 3,
    };

    m_vao.create();
    m_vao.bind();

    // Create vertex buffer
    m_vertexBuffer = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vertexBuffer.create();
    m_vertexBuffer.bind();
    m_vertexBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    m_vertexBuffer.allocate(20 * sizeof(float));

    // Create index buffer
    m_indexBuffer = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.allocate(indices, sizeof(indices));

    // Enable vertex attributes
    m_shaderProgram->bind();
    m_shaderProgram->enableAttributeArray(0);
    m_shaderProgram->setAttributeBuffer(
        0, GL_FLOAT,
        0, 3,
        5 * sizeof(GLfloat)); // Positions

    m_shaderProgram->enableAttributeArray(1);
    m_shaderProgram->setAttributeBuffer(
        1, GL_FLOAT,
        3 * sizeof(GLfloat),
        2, 5 * sizeof(GLfloat)); // Texture Coords
    m_shaderProgram->release();

    m_vao.release();
    m_vertexBuffer.release();
    m_indexBuffer.release();
}

void CanvasWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    m_controller->transform()->updateProjection(static_cast<float>(width) / height);
    update();
}

void CanvasWidget::paintGL()
{
    glClearColor(0.26, 0.26, 0.26, 1.0); // Set background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    if (!m_shaderProgram)
        return;

    for (int yInd = 0; yInd < m_textures.size(); ++yInd) {
        for (int xInd = 0; xInd < m_textures[yInd].size(); ++xInd) {
            renderChunk(xInd, yInd);
        }
    }

    glFlush();
}

void CanvasWidget::renderChunk(const int xInd, const int yInd)
{
    m_shaderProgram->bind();
    m_shaderProgram->setUniformValue("uTransform", m_controller->transform()->m_mvp);

    const auto texture = m_textures.at(yInd).at(xInd);
    const auto &rect = m_controller->image()->mergedLayer()->getChunk(xInd, yInd)->rect;

    m_vao.bind();
    m_vertexBuffer.bind();
    m_indexBuffer.bind();
    texture->bind();
    m_vertexBuffer.write(0, rect.vertices.data(), 20 * sizeof(GLfloat));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    texture->release();
    m_vertexBuffer.release();
    m_indexBuffer.release();
    m_vao.release();
    m_shaderProgram->release();
}

void CanvasWidget::tabletEvent(QTabletEvent *event)
{
    m_eventHandler->tabletEvent(event);
}

void CanvasWidget::wheelEvent(QWheelEvent *event)
{
    m_eventHandler->wheelEvent(event);
    update();
}

void CanvasWidget::mousePressEvent(QMouseEvent *event)
{
    m_eventHandler->mousePressEvent(event);
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_eventHandler->mouseReleaseEvent(event);

}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event)
{
    m_eventHandler->mouseMoveEvent(event);
}

void CanvasWidget::resizeEvent(QResizeEvent *event)
{
    QOpenGLWidget::resizeEvent(event);

    const int newWidth = event->size().width();
    const int newHeight = event->size().height();

    m_eventHandler->setSize(newWidth, newHeight);
    resizeGL(newWidth, newHeight);
}

}
