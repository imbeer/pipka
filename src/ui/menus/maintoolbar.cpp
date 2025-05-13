#include "maintoolbar.h"

#include <QVBoxLayout>

#include "elements/splitter.h"
#include "elements/buttons/menubutton.h"
#include <QFileDialog>

namespace PIPKA::UI {

MainToolBar::MainToolBar(
    const std::shared_ptr<CONTROL::Controller> &controller,
    const int &x, const int &y,
    const int &w, const int &h,
    QWidget *parent) :
    FloatingWidget(x, y, w, h, parent), m_controller{controller},
    m_xMargin(x), m_yMargin(y), m_fullWidth(w), m_prefferedHeight(h)
{
    setFixedWidth(w);
    initUi();
}

void MainToolBar::onWindowResize(const QSize &newWindowSize)
{
    const int h = newWindowSize.height() - 2 * m_yMargin;
    m_prefferedHeight = h;
    if (!m_isCollapsed) {
        resize(width(), h);
    }
}

void MainToolBar::switchCollapseState()
{
    if (m_isCollapsed) {
        m_isCollapsed = false;
        m_currentMenu->show();
        resize(m_fullWidth, m_prefferedHeight);
    } else {
        m_isCollapsed = true;
        m_currentMenu->hide();
        resize(m_fullWidth, m_topBar->height());
    }
}

void MainToolBar::save() const
{
    const QString fileName = QFileDialog::getSaveFileName(
       nullptr,
       tr("Save Image"),
       "./output.png",
       tr("PNG Image (*.png);;All Files (*)")
   );
    m_controller->saveImage(fileName);
}

void MainToolBar::switchCurrentMenu()
{
    if (m_currentMenu == m_toolMenu) {
        m_currentMenu = m_fileMenu;
        m_toolMenu->hide();
    } else {
        m_currentMenu = m_toolMenu;
        m_fileMenu->hide();
    }
    m_currentMenu->show();
    if (m_isCollapsed) {
        switchCollapseState();
    }
}

void MainToolBar::initUi()
{
    m_colorSelector = new ColorSelectorWidget(m_controller);
    m_layerList = new LayerList(m_controller, 248, 40, this);
    m_brushList = new BrushList(m_controller, 248, 40, this);
    m_topBar = new TopBar(this);

    connect(m_topBar, &TopBar::hideMenu, this, &MainToolBar::switchCollapseState);
    connect(m_topBar, &TopBar::save, this, &MainToolBar::save);
    connect(m_topBar, &TopBar::changeMenu, this, &MainToolBar::switchCurrentMenu);

    const auto layout = new QVBoxLayout(this);
    setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    layout->setSpacing(0);

    initToolMenuUi();
    initFileMenuUi();

    m_currentMenu = m_toolMenu;
    m_fileMenu->hide();

    layout->addWidget(m_topBar);
    layout->addWidget(m_toolMenu);
    layout->addWidget(m_fileMenu);
}

void MainToolBar::initFileMenuUi()
{
    m_fileMenu = new QWidget(this);
    const auto innerLayout = new QVBoxLayout(m_fileMenu);
    innerLayout->setContentsMargins(16, 0, 16, 0);
    innerLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter | Qt::AlignAbsolute);
    innerLayout->setSpacing(10);
    innerLayout->addWidget(m_topBar);
    m_fileMenu->setLayout(innerLayout);

    const auto openButton = new MenuButton(230, 30, 10, "Open", m_fileMenu);
    const auto saveButton = new MenuButton(230, 30, 10, "Save", m_fileMenu);
    const auto newButton = new MenuButton(230, 30, 10, "New", m_fileMenu);

    innerLayout->addWidget(new Splitter(this));
    innerLayout->addWidget(openButton);
    innerLayout->addWidget(saveButton);
    innerLayout->addWidget(newButton);
    innerLayout->addWidget(new Splitter(this));
}

void MainToolBar::initToolMenuUi()
{
    m_toolMenu = new QWidget(this);
    const auto innerLayout = new QVBoxLayout(m_toolMenu);
    innerLayout->setContentsMargins(0, 0, 0, 0);
    innerLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter | Qt::AlignAbsolute);
    innerLayout->setSpacing(0);
    innerLayout->addWidget(m_topBar);
    m_toolMenu->setLayout(innerLayout);

    innerLayout->addWidget(new Splitter(this));
    innerLayout->addWidget(m_colorSelector);
    innerLayout->addWidget(new Splitter(this));
    innerLayout->addWidget(m_brushList);
    innerLayout->addWidget(new Splitter(this));
    innerLayout->addWidget(m_layerList);
    innerLayout->addWidget(new Splitter(this));
}

}
