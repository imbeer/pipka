#include "maintoolbar.h"

#include <QVBoxLayout>

#include "elements/splitter.h"

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

void MainToolBar::collapse()
{
    if (m_isCollapsed) {
        m_isCollapsed = false;
        m_box->show();
        update();

    } else {
        m_isCollapsed = true;
        m_box->hide();
        update();
        // resize(m_topBar->width(), m_topBar->height());
    }
}

void MainToolBar::save() const
{
    m_controller->saveImage();
}

void MainToolBar::swapMenu()
{
    // todo: change menu to files
    return;
}

void MainToolBar::initUi()
{
    m_colorSelector = new ColorSelectorWidget(m_controller);
    m_layerList = new LayerList(m_controller, 248, 40, this);
    m_brushList = new BrushList(m_controller, 248, 40, this);
    m_topBar = new TopBar(this);

    connect(m_topBar, &TopBar::hideMenu, this, &MainToolBar::collapse);
    connect(m_topBar, &TopBar::save, this, &MainToolBar::save);
    connect(m_topBar, &TopBar::changeMenu, this, &MainToolBar::swapMenu);

    const auto layout = new QVBoxLayout(this);
    setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    layout->setSpacing(0);

    m_box = new QWidget(this);
    const auto innerLayout = new QVBoxLayout(m_box);
    innerLayout->setContentsMargins(0, 0, 0, 0);
    innerLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter | Qt::AlignAbsolute);
    innerLayout->setSpacing(0);
    innerLayout->addWidget(m_topBar);
    m_box->setLayout(innerLayout);

    innerLayout->addWidget(new Splitter(this));
    innerLayout->addWidget(m_colorSelector);
    innerLayout->addWidget(new Splitter(this));
    innerLayout->addWidget(m_brushList);
    innerLayout->addWidget(new Splitter(this));
    innerLayout->addWidget(m_layerList);
    innerLayout->addWidget(new Splitter(this));

    layout->addWidget(m_topBar);
    layout->addWidget(m_box);
}

}
