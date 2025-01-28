// #include "widgets/canvaswidget.h"

#include <QApplication>
#include "widgets/canvaswidget.h"
#include "image/image.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PIPKA::IMAGE::Image image(10, 10);
    CanvasWidget w(image);
    w.resize(400, 400);
    w.show();
    return a.exec();
}
