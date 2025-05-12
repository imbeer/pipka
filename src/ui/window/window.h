#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

#include "eventhandler.h"
#include "../../control/controller.h"
#include "../menus/floatingwidget.h"

namespace PIPKA::UI {

class Window final : public QMainWindow
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);
    ~Window() override;
    void setController(std::shared_ptr<CONTROL::Controller> &controller);

private:
    void initUi();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    // todo: add events;

private:
    std::vector<std::shared_ptr<FloatingWidget>> m_menus;
    EventHandler *m_eventHandler = nullptr;
    QWidget *m_canvas = nullptr;
};

}

#endif // WINDOW_H
