#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLShader>
#include <QOpenGLBuffer>

#include "../control/controller.h"

using namespace CONTROL;

namespace WIDGET
{

class CanvasWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    CanvasWidget(QWidget *parent = nullptr);
    ~CanvasWidget();
    // void setPicture(const Picture *picture);

protected:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

private:
    void initializeOpenGLFunctions();
    void initShaders();
    void initGeometry();
    void updateTextureArray();
    void clearTextures();

private:
    Controller m_controller;
    QOpenGLShaderProgram m_program;
    QOpenGLBuffer m_vertexBuffer;
    QOpenGLBuffer m_uvBuffer;
    QOpenGLTexture* m_textureArray = nullptr;
    int m_textureNum;
};

}
#endif // CANVASWIDGET_H
