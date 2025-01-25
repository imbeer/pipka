#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QTabletEvent>

class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    CanvasWidget(QWidget *parent = nullptr);
    ~CanvasWidget();

protected:
    void tabletEvent(QTabletEvent *event) override;
};
#endif // CANVASWIDGET_H
