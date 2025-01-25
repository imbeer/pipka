// #include "widgets/canvaswidget.h"

#include <QApplication>
#include "widgets/canvaswidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CanvasWidget w;
    w.resize(800, 600);
    w.show();
    return a.exec();
}
