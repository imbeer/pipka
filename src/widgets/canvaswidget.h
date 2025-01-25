#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QtOpenGL/QOpenGLTexture>
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLVertexArrayObject>
#include <QTabletEvent>

#include "../image/layer.h"

class CanvasWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    CanvasWidget(QWidget *parent = nullptr);
    ~CanvasWidget();

protected:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

protected:
    void tabletEvent(QTabletEvent *event) override;

// qt draws one texture at a time. So basically I need vector<Texture> and then just bind them and draw.
//
private:
    QOpenGLTexture* m_texture;
    PIPKA::IMAGE::Layer m_layer;
    QOpenGLShaderProgram* m_shaderProgram;
    QOpenGLBuffer m_vertexBuffer;
    QOpenGLBuffer m_indexBuffer;
    QOpenGLVertexArrayObject m_vao;
};
#endif // CANVASWIDGET_H
