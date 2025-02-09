#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "../control/controller.h"

namespace PIPKA::UI {

class Window : public QMainWindow
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);

private:
    void initUi();

public:
    void setController(std::shared_ptr<PIPKA::CONTROL::Controller> &controller);

};

}

#endif // WINDOW_H
