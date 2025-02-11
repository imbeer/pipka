#include "maintoolbar.h"

#include <QVBoxLayout>

namespace PIPKA::UI {

MainToolBar::MainToolBar(
    std::shared_ptr<PIPKA::CONTROL::Controller> &controller,
    const int &x, const int &y,
    const int &w, const int &h,
    QWidget *parent)
    : FloatingWidget(x, y, w, h, parent), m_controller{controller}
{
    initUi();
}

void MainToolBar::initUi()
{
    m_layerList = new LayerList(m_controller, 248, 500, this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(m_layerList);
}

}
