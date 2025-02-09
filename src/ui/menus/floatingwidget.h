#ifndef FLOATINGWIDGET_H
#define FLOATINGWIDGET_H

#include <QWidget>

namespace PIPKA::UI {

class FloatingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FloatingWidget(
        const int &x, const int &y,
        const int &w, const int &h,
        QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);

};

}

#endif // FLOATINGWIDGET_H
