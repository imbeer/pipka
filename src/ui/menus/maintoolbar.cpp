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
    m_colorSelector = new ColorSelectorWidget(m_controller);
    m_layerList = new LayerList(m_controller, 248, 40, this);
    const auto layout = new QVBoxLayout(this);
    setLayout(layout);
    layout->setContentsMargins(0, 28, 0, 0);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(0);
    layout->addWidget(m_colorSelector);
    layout->addWidget(m_layerList);
}

}
