#ifndef MAINTOOLBAR_H
#define MAINTOOLBAR_H

#include "floatingwidget.h"
#include "lists/layerlist/layerlist.h"
#include "lists/brushlist/brushlist.h"
#include "../../control/controller.h"
#include "elements/topbar.h"
#include "tools/colorselectorwidget.h"

namespace PIPKA::UI {

class MainToolBar : public FloatingWidget
{
public:
    explicit MainToolBar(
        const std::shared_ptr<CONTROL::Controller> &m_controller,
        const int &x = 10, const int &y = 10,
        const int &w = 256, const int &h = 1000,
        QWidget *parent = nullptr);
    void onWindowResize(const QSize &newWindowSize) override;

    void switchCollapseState();
    void save() const;
    void create() const;
    void switchCurrentMenu();

private:
    void initUi();
    void initFileMenuUi();
    void initToolMenuUi();

private:
    std::shared_ptr<CONTROL::Controller> m_controller;
    LayerList *m_layerList;
    BrushList *m_brushList;
    TopBar *m_topBar;
    ColorSelectorWidget *m_colorSelector;
    const int m_yMargin;
    const int m_xMargin;
    const int m_fullWidth;
    int m_prefferedHeight;
    QWidget *m_toolMenu;
    QWidget *m_fileMenu;
    QWidget *m_currentMenu;
    bool m_isCollapsed{false};
};

}

#endif // MAINTOOLBAR_H
