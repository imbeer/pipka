#include "maintoolbar.h"

#include <QVBoxLayout>

#include "elements/splitter.h"
#include "elements/buttons/menubutton.h"
#include <QFileDialog>

#include "elements/dialogs/createdialog.h"

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
    if (!fileName.isEmpty()) {
        m_controller->saveImage(fileName);
    }
}

void MainToolBar::create() const
{
    CreateDialog dialog;
    if (dialog.exec() == QDialog::Accepted) {
        const int width = dialog.widthValue();
        const int height = dialog.heightValue();
        if (width <= 0 || height <= 0) {
            // todo: add error dialog
            return;
        }
        m_controller->createImage(width, height);
    }
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

    const auto innerBox = new QWidget(m_fileMenu);
    const auto innerLayout = new QVBoxLayout(m_fileMenu);
    innerLayout->setSpacing(10);
    innerLayout->setContentsMargins(0, 0, 0, 0);

    innerLayout->addWidget(new Splitter(this));
    innerLayout->addWidget(innerBox);
    innerLayout->addWidget(new Splitter(this));

    const auto innerMarginedLayout = new QVBoxLayout(innerBox);
    innerMarginedLayout->setContentsMargins(16, 0, 16, 0);
    innerMarginedLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter | Qt::AlignAbsolute);
    innerMarginedLayout->setSpacing(10);

    const auto openButton = new MenuButton(230, 30, 10, "Open", innerBox);
    const auto saveButton = new MenuButton(230, 30, 10, "Save", innerBox);
    const auto createButton = new MenuButton(230, 30, 10, "New", innerBox);

    connect(saveButton, &MenuButton::pressed, this, &MainToolBar::save);
    connect(createButton, &MenuButton::pressed, this, &MainToolBar::create);

    innerMarginedLayout->addWidget(openButton);
    innerMarginedLayout->addWidget(saveButton);
    innerMarginedLayout->addWidget(createButton);

    innerBox->setLayout(innerMarginedLayout);
    m_fileMenu->setLayout(innerLayout);
}

void MainToolBar::initToolMenuUi()
{
    m_colorSelector = new ColorSelectorWidget(m_controller);
    m_layerList = new LayerList(m_controller, 248, 40, this);
    m_brushList = new BrushList(m_controller, 248, 40, this);
    m_toolMenu = new QWidget(this);
    const auto innerLayout = new QVBoxLayout(m_toolMenu);
    innerLayout->setContentsMargins(0, 0, 0, 0);
    innerLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter | Qt::AlignAbsolute);
    innerLayout->setSpacing(0);

    innerLayout->addWidget(new Splitter(this));
    innerLayout->addWidget(m_colorSelector);
    innerLayout->addWidget(new Splitter(this));
    innerLayout->addWidget(m_brushList);
    innerLayout->addWidget(new Splitter(this));
    innerLayout->addWidget(m_layerList);
    innerLayout->addWidget(new Splitter(this));

    m_toolMenu->setLayout(innerLayout);
}

}
