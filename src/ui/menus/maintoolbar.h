#ifndef MAINTOOLBAR_H
#define MAINTOOLBAR_H

#include "floatingwidget.h"
#include "lists/layerlist.h"
#include "../../control/controller.h"
#include "tools/colorselectorwidget.h"

namespace PIPKA::UI {

class MainToolBar : public FloatingWidget
{
public:
    MainToolBar(
        const std::shared_ptr<CONTROL::Controller> &m_controller,
        const int &x = 10, const int &y = 10,
        const int &w = 256, const int &h = 1000,
        QWidget *parent = nullptr);
    void onWindowResize(const QSize &newWindowSize) override;

private:
    void initUi();

private:
    std::shared_ptr<CONTROL::Controller> m_controller;
    LayerList *m_layerList;
    ColorSelectorWidget *m_colorSelector;
    const int m_yMargin;
    const int m_xMargin;
};

}

#endif // MAINTOOLBAR_H
