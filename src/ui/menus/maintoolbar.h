#ifndef MAINTOOLBAR_H
#define MAINTOOLBAR_H

#include "floatingwidget.h"
#include "layerlist.h"
#include "../../control/controller.h"

namespace PIPKA::UI {

class MainToolBar : public FloatingWidget
{
public:
    MainToolBar(
        std::shared_ptr<PIPKA::CONTROL::Controller> &m_controller,
        const int &x = 10, const int &y = 10,
        const int &w = 256, const int &h = 1000,
        QWidget *parent = nullptr);

private:
    void initUi();

private:
    std::shared_ptr<PIPKA::CONTROL::Controller> m_controller;
    ToolList *m_layerList;
};

}

#endif // MAINTOOLBAR_H
