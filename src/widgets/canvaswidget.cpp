#include "canvaswidget.h"

CanvasWidget::CanvasWidget(QWidget *parent)
    : QOpenGLWidget(parent),
    m_layer(16, 16, 0xFFAAAAFF)
{}

CanvasWidget::~CanvasWidget()
{
    if (m_texture) {
        delete m_texture;
        m_texture = nullptr;
    }
    if (m_shaderProgram) {
        delete m_shaderProgram;
        m_shaderProgram = nullptr;
    }
}

void CanvasWidget::initializeGL()
{
    initializeOpenGLFunctions();

    m_texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
    m_texture->setSize(m_layer.width(), m_layer.height());
    m_texture->setFormat(QOpenGLTexture::RGBA8_UNorm);
    m_texture->allocateStorage();
    m_texture->setData(QOpenGLTexture::RGBA, QOpenGLTexture::UInt8,
                     reinterpret_cast<const void*>(m_layer.pixels().data()));

    m_shaderProgram = new QOpenGLShaderProgram();
    m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/canvas_vertex_shader.vert");
    m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/canvas_fragment_shader.frag");
    m_shaderProgram->link();

    static const GLfloat vertices[] = {
        // Positions    // Texture Coords
        -1.0f, -1.0f,   0.0f, 0.0f,
        1.0f, -1.0f,   1.0f, 0.0f,
        -1.0f,  1.0f,   0.0f, 1.0f,
        1.0f,  1.0f,   1.0f, 1.0f,
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
    m_shaderProgram->setAttributeBuffer(0, GL_FLOAT, 0, 2, 4 * sizeof(GLfloat)); // Positions

    m_shaderProgram->enableAttributeArray(1);
    m_shaderProgram->setAttributeBuffer(1, GL_FLOAT, 2 * sizeof(GLfloat), 2, 4 * sizeof(GLfloat)); // Texture Coords
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
    glClear(GL_COLOR_BUFFER_BIT);

    if (m_texture && m_shaderProgram) {
        m_texture->bind();
        m_shaderProgram->bind();

        m_shaderProgram->setUniformValue("uTexture", 0); // Texture unit 0

        m_vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        m_vao.release();

        m_shaderProgram->release();
        m_texture->release();
    }
}

void CanvasWidget::tabletEvent(QTabletEvent *event)
{
    qDebug() << event->pressure();
}
