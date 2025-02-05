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
    auto image = m_controller.getImage();
    for (int layerInd = 0; layerInd < image->layerSize(); layerInd++) {
        addTexture(layerInd);
    }
    auto res = QObject::connect(
        image.get(), &PIPKA::IMAGE::Image::layerAdded,
        this, &CanvasWidget::addTexture);
    if (res) {
        qDebug() << "connected";
    }
}

void CanvasWidget::addTexture(const int &index) // todo: add check for vector bounds or something idk
{
    auto image = m_controller.getImage();
    auto layer = image->layers()[index];
    auto texture = std::make_shared<QOpenGLTexture>(QOpenGLTexture::Target2D);

    texture->setSize(image->width(), image->height());
    texture->setFormat(QOpenGLTexture::RGBA8_UNorm);
    texture->allocateStorage();
    texture->setMinMagFilters(QOpenGLTexture::Filter::Nearest, QOpenGLTexture::Filter::Nearest);
    texture->setData(QOpenGLTexture::RGBA, QOpenGLTexture::UInt8,
                     reinterpret_cast<const void*>(layer->pixels().data()));
    // m_textures.push_back(texture);
    m_textures.insert(m_textures.begin() + index, texture);

    auto res = QObject::connect(
        image->layers()[index].get(), &PIPKA::IMAGE::Layer::layerChanged,
        this, &CanvasWidget::updateTextureData);
    if (res) {
        qDebug() << "connected";
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
    m_controller.updateProjection(static_cast<float>(width) / height);
    update();
}

void CanvasWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color

    // glDisable(GL_DEPTH_TEST);
    // glDisable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glEnable(GL_TEXTURE_2D);
    // glDepthMask(GL_FALSE);

    if (!m_textures.empty() && m_shaderProgram) {
        m_shaderProgram->bind();
        m_vao.bind();
        qDebug() << m_textures.size();
        m_shaderProgram->setUniformValue("uTransform", m_controller.transform());
        for (const auto &texture : m_textures) {
            texture->bind();
            m_shaderProgram->setUniformValue("uTexture", 0); // Texture unit 0
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            // qDebug() << "draw texture";
            texture->release();
        }

        m_vao.release();
        m_shaderProgram->release();
    }
    // glDisable(GL_BLEND);
    glFlush();
}

void CanvasWidget::tabletEvent(QTabletEvent *event)
{
    auto point = getNormalizedClickVector(event->position(), event->pressure());
    //
    switch (event->type()) {
    case QEvent::TabletPress:
        m_controller.handleClick(point.x(), point.y(), point.z());
        break;
    case QEvent::TabletRelease:
        m_controller.handleRelease(point.x(), point.y(), point.z());
        break;
    case QEvent::TabletMove:
        m_controller.handleMove(point.x(), point.y(), point.z());
        break;
    default:
        break;
    }
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

void CanvasWidget::mousePressEvent(QMouseEvent *event)
{
    // m_mousePressed = true;
    auto point = getNormalizedClickVector(event->position());
    m_controller.handleClick(point.x(), point.y(), point.z());
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event)
{
    // m_mousePressed = false;
    auto point = getNormalizedClickVector(event->position());
    m_controller.handleRelease(point.x(), point.y(), point.z());
}
void CanvasWidget::mouseMoveEvent(QMouseEvent *event)
{
    // if (m_mousePressed)
    //     getNormalizedClickVector(event->position());
    auto point = getNormalizedClickVector(event->position());
    m_controller.handleMove(point.x(), point.y(), point.z());
}

void CanvasWidget::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    switch (key) {
        case Qt::Key_R:
            m_controller.rotateRight();
            break;
        case Qt::Key_Q:
            m_controller.rotateLeft();
            break;
        case Qt::Key_S:
            m_controller.moveUp();
            break;
        case Qt::Key_W:
            m_controller.moveDown();
            break;
        case Qt::Key_D:
            m_controller.moveLeft();
            break;
        case Qt::Key_A:
            m_controller.moveRight();
            break;
        case Qt::Key_Backspace:
            m_controller.clearActiveLayer();
            break;
        case Qt::Key_L:
            m_controller.addLayer();
            break;
        default:
            break;
    }
    update();
}

void CanvasWidget::resizeEvent(QResizeEvent *event)
{
    QOpenGLWidget::resizeEvent(event);

    qDebug() << "resized";

    int newWidth = event->size().width();
    int newHeight = event->size().height();

    resizeGL(newWidth, newHeight);
}

QVector3D CanvasWidget::getNormalizedClickVector(const QPointF &position, const double &pressure)
{
    double x = 2.0 * position.x() / width() - 1.0;
    double y = 1.0 - 2.0 * position.y() / height();
    return QVector3D(x, y, pressure);
}
