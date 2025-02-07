// #include "widgets/canvaswidget.h"

#include <QApplication>
#include "ui/canvaswidget.h"
#include "controller/controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // PIPKA::IMAGE::Image image(10, 10);
    auto controller = std::make_shared<PIPKA::CONTROL::Controller>();
    controller->createImage(1024, 1024);
    PIPKA::UI::CanvasWidget w(controller);
    w.resize(800, 800);
    w.show();
    return a.exec();
}
