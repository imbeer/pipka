#include "canvaswidget.h"

namespace  WIDGET {

CanvasWidget::CanvasWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{

}

CanvasWidget::~CanvasWidget()
{
    m_vertexBuffer.destroy();
    m_uvBuffer.destroy();
    clearTextures();
}

void CanvasWidget::initializeGL()
{
    initializeOpenGLFunctions();
    initGeometry();
    initShaders();
}

void CanvasWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void CanvasWidget::paintGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT);
    m_textureArray->bind();

    m_program.bind();
    m_vertexBuffer.bind();
    m_program.enableAttributeArray(0);
    m_program.setAttributeBuffer(0, GL_FLOAT, 0, 3, sizeof(QVector3D));
    m_uvBuffer.bind();
    m_program.enableAttributeArray(1);
    m_program.setAttributeBuffer(1, GL_FLOAT, 0, 2, sizeof(QVector2D));

    f->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    m_program.disableAttributeArray(0);
    m_program.disableAttributeArray(1);

    m_program.release();
    m_textureArray->release();
}

void CanvasWidget::initShaders()
{
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertex_shader.vsh"))
        qDebug() << "vertex shader";
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.fsh"))
        qDebug() << "fragment shader";
    if (!m_program.link())
        qDebug() << "shader link";
}

void CanvasWidget::initGeometry()
{
    // todo: make it fit image ratio
    QVector3D vertices[] = {
        QVector3D(-1.0f, -1.0f, 0.0f), /// Bottom-left
        QVector3D( 1.0f, -1.0f, 0.0f), /// Bottom-right
        QVector3D(-1.0f,  1.0f, 0.0f), /// Top-left
        QVector3D( 1.0f,  1.0f, 0.0f)  /// Top-right
    };

    QVector2D uvs[] = {
        QVector2D(0.0f, 1.0f), /// Top-left
        QVector2D(1.0f, 1.0f),  /// Top-right
        QVector2D(0.0f, 0.0f), /// Bottom-left
        QVector2D(1.0f, 0.0f) /// Bottom-right
    };

    m_vertexBuffer.create();
    m_vertexBuffer.bind();
    m_vertexBuffer.allocate(vertices, sizeof(vertices));

    m_uvBuffer.create();
    m_uvBuffer.bind();
    m_uvBuffer.allocate(uvs, sizeof(uvs));
}

void CanvasWidget::updateTextureArray()
{
    clearTextures();
    m_program.bind();
    m_textureNum = m_controller.picture().layers().size();
    m_program.setUniformValue("textureNum", m_textureNum);
    const int width = m_controller.picture().width();
    const int height = m_controller.picture().height();

    if (m_textureNum == 0 || (width == 0 && height == 0)) {
        m_program.setUniformValue("textureArray", 0);
        m_program.release();
        return;
    }

    m_textureArray = new QOpenGLTexture(QOpenGLTexture::Target2DArray);
    m_textureArray->setFormat(QOpenGLTexture::RGBA32F);
    m_textureArray->setSize(width, height, m_textureNum);
    m_textureArray->allocateStorage();

    for (int i = 0; i < m_textureNum; ++i) {
        // Check if works.
        m_textureArray->setData(0, i, QOpenGLTexture::RGBA, QOpenGLTexture::Float32, m_controller.picture().layers()[i].pixels());
    }
    m_textureArray->setWrapMode(QOpenGLTexture::ClampToBorder);
    m_textureArray->setBorderColor(1.0f, 1.0f, 1.0f, 1.0f);
    m_textureArray->setMinificationFilter(QOpenGLTexture::Linear);
    m_textureArray->setMagnificationFilter(QOpenGLTexture::Linear);

    m_program.setUniformValue("textureArray", 0);
    m_program.release();
}

void CanvasWidget::clearTextures()
{
    if (m_textureArray) {
        delete m_textureArray;
        m_textureArray = nullptr;
    }
}

}
