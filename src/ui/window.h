#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "../control/controller.h"
#include "menus/floatingwidget.h"

namespace PIPKA::UI {

class Window final : public QMainWindow
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);
    void setController(std::shared_ptr<PIPKA::CONTROL::Controller> &controller);

private:
    void initUi();

protected:
    // void moveEvent(QMoveEvent *event) override;

private:
    std::vector<std::shared_ptr<FloatingWidget>> m_menus;
};

}

#endif // WINDOW_H
