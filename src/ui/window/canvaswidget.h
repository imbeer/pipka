#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QtOpenGL/QOpenGLTexture>
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLVertexArrayObject>

#include "../../control/controller.h"
#include "eventhandler.h"

namespace PIPKA::UI {

class CanvasWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit CanvasWidget(
        const std::shared_ptr<CONTROL::Controller> &controller,
        EventHandler *eventHandler,
        QWidget *parent = nullptr);
    ~CanvasWidget() override;
    void callUpdate() {this->update();}

private:
    void initializeTextures();
    void updateTextureData(int xInd, int yInd);
    // void addTexture(const int &index);
    // void updateWholeTextureData();
    void connectTextures();

protected:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;
    void renderChunk(int xInd, int yInd);

protected:
    // todo: slap event filter here
    void tabletEvent      (QTabletEvent *event) override;
    void wheelEvent       (QWheelEvent *event) override;
    void mousePressEvent  (QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent   (QMouseEvent *event) override;
    void resizeEvent      (QResizeEvent *event) override;

private:
    EventHandler *m_eventHandler;
    std::vector<std::vector<std::shared_ptr<QOpenGLTexture>>> m_textures;
    std::shared_ptr<CONTROL::Controller> m_controller;
    QOpenGLShaderProgram* m_shaderProgram;
    QOpenGLBuffer m_vertexBuffer;
    QOpenGLBuffer m_indexBuffer;
    QOpenGLVertexArrayObject m_vao;
};

}

#endif // CANVASWIDGET_H
