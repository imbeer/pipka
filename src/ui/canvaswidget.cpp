#include "canvaswidget.h"

#include <QOpenGLPixelTransferOptions>

namespace PIPKA::UI {

CanvasWidget::CanvasWidget(
    const std::shared_ptr<CONTROL::Controller> &controller,
    QWidget *parent)
    : QOpenGLWidget(parent),
      m_eventHandler(controller, width(), height()),
      m_controller(controller), m_shaderProgram(nullptr)
{
}

CanvasWidget::~CanvasWidget()
{
    m_texture->destroy();
    if (m_shaderProgram) {
        delete m_shaderProgram;
        m_shaderProgram = nullptr;
    }
}

void CanvasWidget::initializeTextures()
{
    const auto image = m_controller->getImage();
    m_texture = std::make_shared<QOpenGLTexture>(QOpenGLTexture::Target2D);

    m_texture->setSize(image->width(), image->height());
    m_texture->setFormat(QOpenGLTexture::RGBA8_UNorm);
    m_texture->allocateStorage();
    m_texture->setMinMagFilters(QOpenGLTexture::Filter::Nearest, QOpenGLTexture::Filter::Nearest);
    m_texture->setData(
        QOpenGLTexture::BGRA,
        QOpenGLTexture::UInt8,
        image->pixels().data());

    connect(
        image.get(), &IMAGE::Image::pixelChanged,
        this, &CanvasWidget::updateTextureData);
    connect(
        image.get(), &IMAGE::Image::allPixelsChanged,
        this, &CanvasWidget::updateWholeTextureData);
}

void CanvasWidget::updateTextureData(const int &x, const int &y)
{
    const int w = m_controller->getImage()->width();
    // const int h = m_controller->getImage()->height();
    const int pixelInd = y * w + x;

    const IMAGE::Color pixel = m_controller->getImage()->pixels()[pixelInd];
    qDebug() << "texture updated";
    const uint8_t pixelData[4] = {
        static_cast<uint8_t>(pixel & 0xFF),          // Blue
        static_cast<uint8_t>(pixel >> 8 & 0xFF),   // Green
        static_cast<uint8_t>(pixel >> 16 & 0xFF),  // Red
        static_cast<uint8_t>(pixel >> 24 & 0xFF)   // Alpha
    };
    m_texture->bind();
    glTexSubImage2D(
        GL_TEXTURE_2D,
        0, x, y, 1, 1,
        QOpenGLTexture::BGRA,
        QOpenGLTexture::UInt8,
        pixelData);
    m_texture->release();
    update();
}

void CanvasWidget::updateWholeTextureData()
{
    // m_texture->bind();
    m_texture->setData(
        QOpenGLTexture::BGRA,
        QOpenGLTexture::UInt8,
        m_controller->getImage()->pixels().data());
    // m_texture->release();
    qDebug() << "Calls whole texture update";
    update();
}

void CanvasWidget::initializeGL()
{
    initializeOpenGLFunctions();
    // qDebug() << "initializing textures";
    initializeTextures();
    m_shaderProgram = new QOpenGLShaderProgram();
    m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/canvas_vertex_shader.vert");
    m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/canvas_fragment_shader.frag");
    m_shaderProgram->link();

    static constexpr GLfloat vertices[] = {
        // Positions    // Texture Coords
       -1.0f, -1.0f, 1.0,  0.0f, 0.0f,
        1.0f, -1.0f, 1.0,  1.0f, 0.0f,
       -1.0f,  1.0f, 1.0,  0.0f, 1.0f,
        1.0f,  1.0f, 1.0,  1.0f, 1.0f,
    };

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
    m_vertexBuffer.allocate(vertices, sizeof(vertices));

    // Create index buffer
    m_indexBuffer = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.allocate(indices, sizeof(indices));

    // Enable vertex attributes
    m_shaderProgram->bind();
    m_shaderProgram->enableAttributeArray(0);
    m_shaderProgram->setAttributeBuffer(0, GL_FLOAT, 0, 3, 5 * sizeof(GLfloat)); // Positions

    m_shaderProgram->enableAttributeArray(1);
    m_shaderProgram->setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(GLfloat), 2, 5 * sizeof(GLfloat)); // Texture Coords
    m_shaderProgram->release();

    m_vao.release();
    m_vertexBuffer.release();
    m_indexBuffer.release();
}

void CanvasWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    m_controller->updateProjection(static_cast<float>(width) / height);
    update();
}

void CanvasWidget::paintGL()
{
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    if (m_texture && m_shaderProgram) {
        m_shaderProgram->bind();
        m_vao.bind();
        m_shaderProgram->setUniformValue("uTransform", m_controller->transform());
        // for (const auto &texture : m_textures) {
        m_texture->bind();
        // m_shaderProgram->setUniformValue("uTexture", 0); // Texture unit 0
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        m_texture->release();
        // }
        m_vao.release();
        m_shaderProgram->release();

    }
    glFlush();
}

void CanvasWidget::tabletEvent(QTabletEvent *event)
{
    m_eventHandler.tabletEvent(event);
}

void CanvasWidget::wheelEvent(QWheelEvent *event)
{
    m_eventHandler.wheelEvent(event);
    update();
}

void CanvasWidget::mousePressEvent(QMouseEvent *event)
{
    m_eventHandler.mousePressEvent(event);
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_eventHandler.mouseReleaseEvent(event);

}
void CanvasWidget::mouseMoveEvent(QMouseEvent *event)
{
    m_eventHandler.mouseMoveEvent(event);
}

void CanvasWidget::keyPressEvent(QKeyEvent *event)
{
    m_eventHandler.keyPressEvent(event);
    update();
}

void CanvasWidget::keyReleaseEvent(QKeyEvent *event)
{
    m_eventHandler.keyReleaseEvent(event);
    // update();
}

void CanvasWidget::resizeEvent(QResizeEvent *event)
{
    QOpenGLWidget::resizeEvent(event);

    // qDebug() << "resized";

    const int newWidth = event->size().width();
    const int newHeight = event->size().height();

    m_eventHandler.setSize(newWidth, newHeight);
    resizeGL(newWidth, newHeight);
}


}
