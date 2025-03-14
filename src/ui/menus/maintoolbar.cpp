#include "maintoolbar.h"

#include <QVBoxLayout>

namespace PIPKA::UI {

MainToolBar::MainToolBar(
    const std::shared_ptr<CONTROL::Controller> &controller,
    const int &x, const int &y,
    const int &w, const int &h,
    QWidget *parent)
    : FloatingWidget(x, y, w, h, parent), m_controller{controller}, m_xMargin(x), m_yMargin(y)
{
    initUi();
}

void MainToolBar::onWindowResize(const QSize &newWindowSize)
{
    const int h = newWindowSize.height() - 2 * m_yMargin;
    resize(width(), h);
}

void MainToolBar::initUi()
{
    m_layerList = new LayerList(m_controller, 248, 500, this);
    auto layout = new QVBoxLayout(this); // not leak because set as layout.
    setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(m_layerList);
}

}
