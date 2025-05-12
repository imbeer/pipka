#include "topbar.h"

#include <QHBoxLayout>

#include "buttons/iconbutton.h"

namespace PIPKA::UI
{

TopBar::TopBar(QWidget *parent) :
    QWidget(parent)
{
    initUI();
}

void TopBar::initUI()
{
    const auto layout = new QHBoxLayout(this);
    setFixedHeight(48);
    setLayout(layout);

    const auto changeMenuButton = new IconButton(
        60, 36,
        18, 14, m_changeMenuPixmap, this);
    connect(changeMenuButton, &IconButton::pressed, this, [=]{ emit changeMenu();});

    const auto hideMenuButton = new IconButton(
       60, 36,
       18, 14, m_hideMenuPixmap, this);
    connect(hideMenuButton, &IconButton::pressed, this, [=]{ emit hideMenu();});

    const auto saveButton = new IconButton(
       60, 36,
       18, 14, m_savePixmap, this);
    connect(saveButton, &IconButton::pressed, this, [=]{ emit save();});

    layout->setSpacing(36);
    layout->setContentsMargins(2, 0, 2, 0);
    layout->setAlignment(Qt::AlignAbsolute);
    layout->addWidget(changeMenuButton);
    layout->addWidget(saveButton);
    layout->addWidget(hideMenuButton);
}

}
