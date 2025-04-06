#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

#include "eventhandler.h"
#include "../control/controller.h"
#include "menus/floatingwidget.h"

namespace PIPKA::UI {

class Window final : public QMainWindow
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();
    void setController(std::shared_ptr<CONTROL::Controller> &controller);

private:
    void initUi();

protected:
    void resizeEvent(QResizeEvent *event) override;
    // todo: add events;

private:
    std::vector<std::shared_ptr<FloatingWidget>> m_menus;
    EventHandler *m_eventHandler;
};

}

#endif // WINDOW_H
