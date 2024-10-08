#include <QApplication>

#include "widgets/canvaswidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WIDGET::CanvasWidget widget;
    widget.show();
    // todo: make picture generator
    // todo: set controller to this thing
    return a.exec();
}
