#include <QApplication>
#include "ui/window/window.h"
#include "control/controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto controller = std::make_shared<PIPKA::CONTROL::Controller>();
    controller->createImage(5000, 5000);
    PIPKA::UI::Window w;
    w.setController(controller);
    w.showMaximized();
    return a.exec();
}
