#include "canvaswidget.h"

CanvasWidget::CanvasWidget(
    PIPKA::CONTROL::Controller &controller,
    QWidget *parent)
    : QOpenGLWidget(parent),
    m_controller(controller)
{}

CanvasWidget::~CanvasWidget()
{
    for (auto &texture : m_textures) {
        if (texture) {
            // delete texture;
            texture->destroy();
        }
    }
    m_textures.clear();
    if (m_shaderProgram) {
        delete m_shaderProgram;
        m_shaderProgram = nullptr;
    }
}

void CanvasWidget::initializeTextures()
{
    auto image = m_controller.getImage().value();
    qDebug() << image.layerSize();
    for (int layerInd = 0; layerInd < image.layerSize(); layerInd++) {
        auto layer = image.layers()[layerInd];
        auto texture = std::make_shared<QOpenGLTexture>(QOpenGLTexture::Target2D);

        texture->setSize(image.width(), image.height());
        texture->setFormat(QOpenGLTexture::RGBA8_UNorm);
        texture->allocateStorage();
        texture->setMinMagFilters(QOpenGLTexture::Filter::Nearest, QOpenGLTexture::Filter::Nearest);
        texture->setData(QOpenGLTexture::RGBA, QOpenGLTexture::UInt8,
                         reinterpret_cast<const void*>(layer->pixels().data()));
        m_textures.push_back(texture);

        qDebug() << "one texture added";
        qDebug() << m_textures.size();


        // I guess layer is destructed at the end of scope, so it disconnects.
        auto res = QObject::connect(
            image.layers()[layerInd].get(), &PIPKA::IMAGE::Layer::layerChanged,
            this, &CanvasWidget::updateTextureData);
        if (res) {
            qDebug() << "connected";
        }
    }
}

void CanvasWidget::initializeGL()
{
    initializeOpenGLFunctions();
    qDebug() << "initializing textures";
    initializeTextures();
    m_shaderProgram = new QOpenGLShaderProgram();
    m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/canvas_vertex_shader.vert");
    m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/canvas_fragment_shader.frag");
    m_shaderProgram->link();

    static const GLfloat vertices[] = {
        // Positions    // Texture Coords
       -1.0f, -1.0f, 1.0,  0.0f, 0.0f,
        1.0f, -1.0f, 1.0,  1.0f, 0.0f,
       -1.0f,  1.0f, 1.0,  0.0f, 1.0f,
        1.0f,  1.0f, 1.0,  1.0f, 1.0f,
    };

    static const GLuint indices[] = {
        0, 1, 2,
        2, 1, 3,
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
    update();
}

void CanvasWidget::paintGL()
{
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // Set background color
    glClear(GL_COLOR_BUFFER_BIT);

    if (!m_textures.empty() && m_shaderProgram) {
        m_shaderProgram->bind();
        m_vao.bind();
        for (const auto &texture : m_textures) {
            texture->bind();
            m_shaderProgram->setUniformValue("uTexture", 0); // Texture unit 0
            m_shaderProgram->setUniformValue("uTransform", m_controller.transform());
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            texture->release();
        }

        m_vao.release();
        m_shaderProgram->release();
    }
}

void CanvasWidget::updateTextureData(int index)
{
    m_textures[index]->setData(
        QOpenGLTexture::RGBA,
        QOpenGLTexture::UInt8,
        reinterpret_cast<const void*>(m_controller.getImage()->layers()[index]->pixels().data()));
    qDebug() << "Updated";
    update();
}

void CanvasWidget::tabletEvent(QTabletEvent *event)
{
    qDebug() << event->pressure();
    auto image = m_controller.getImage().value();
    if (!image.layers().empty())
        image.layers()[0]->testDifferentPixels();
}

void CanvasWidget::wheelEvent(QWheelEvent *event)
{
    int delta = event->angleDelta().y();  // Get scroll amount

    if (delta > 0) {
        m_controller.scaleUp();
    } else {
        m_controller.scaleDown();
    }
    update();
}

void CanvasWidget::mousePressEvent(QMouseEvent *event) {
    auto image = m_controller.getImage().value();
    if (!image.layers().empty())
        image.layers()[0]->testDifferentPixels();
}
