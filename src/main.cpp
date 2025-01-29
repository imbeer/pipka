// #include "widgets/canvaswidget.h"

#include <QApplication>
#include "widgets/canvaswidget.h"
#include "controller/controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // PIPKA::IMAGE::Image image(10, 10);
    PIPKA::CONTROL::Controller controller;
    controller.createImage(10, 10);
    CanvasWidget w(controller);
    w.resize(800, 800);
    w.show();
    return a.exec();
}
