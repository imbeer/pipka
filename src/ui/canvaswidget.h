#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QtOpenGL/QOpenGLTexture>
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLVertexArrayObject>

#include "../control/controller.h"
#include "eventhandler.h"

namespace PIPKA::UI {

class CanvasWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit CanvasWidget(
        const std::shared_ptr<CONTROL::Controller> &controller,
        QWidget *parent = nullptr);
    ~CanvasWidget() override;
private:
    void initializeTextures();
    // void addTexture(const int &index);
    void updateTextureData(const int &x, const int &y);
    void updateWholeTextureData();

protected:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

protected:
    // todo: slap event filter here
    void tabletEvent      (QTabletEvent *event) override;
    void wheelEvent       (QWheelEvent *event) override;
    void mousePressEvent  (QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent   (QMouseEvent *event) override;
    void keyPressEvent    (QKeyEvent *event) override;
    void keyReleaseEvent  (QKeyEvent *event) override;
    void resizeEvent      (QResizeEvent *event) override;

// qt draws one texture at a time. So basically I need vector<Texture> and then just bind them and draw.

private:
    EventHandler m_eventHandler;
    std::shared_ptr<QOpenGLTexture> m_texture;
    // QOpenGLTexture* m_texture;
    // PIPKA::IMAGE::Layer m_layer;
    // PIPKA::IMAGE::Image m_image;
    std::shared_ptr<PIPKA::CONTROL::Controller> m_controller;
    QOpenGLShaderProgram* m_shaderProgram;
    QOpenGLBuffer m_vertexBuffer;
    QOpenGLBuffer m_indexBuffer;
    QOpenGLVertexArrayObject m_vao;

    // bool m_mousePressed;
};

}

#endif // CANVASWIDGET_H
