#ifndef MAINTOOLBAR_H
#define MAINTOOLBAR_H

#include "floatingwidget.h"
#include "lists/layerlist.h"
#include "lists/brushlist.h"
#include "../../control/controller.h"

#include "elements/topbar.h"

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

    void collapse();
    void save() const;
    void swapMenu();

private:
    void initUi();

private:
    std::shared_ptr<CONTROL::Controller> m_controller;
    LayerList *m_layerList;
    BrushList *m_brushList;
    TopBar *m_topBar;
    ColorSelectorWidget *m_colorSelector;
    const int m_yMargin;
    const int m_xMargin;
    QWidget *m_box;
    bool m_isCollapsed;
};

}

#endif // MAINTOOLBAR_H
