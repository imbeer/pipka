#include <QApplication>
#include "ui/window.h"
#include "control/controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // PIPKA::IMAGE::Image image(10, 10);
    auto controller = std::make_shared<PIPKA::CONTROL::Controller>();
    controller->createImage(1000, 1000);
    // PIPKA::UI::CanvasWidget w(controller);
    PIPKA::UI::Window w;
    w.setController(controller);
    w.resize(800, 800);
    w.show();
    return a.exec();
}
