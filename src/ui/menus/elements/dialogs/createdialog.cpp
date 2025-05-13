#include "createdialog.h"

#include <QIntValidator>
#include <QVBoxLayout>
#include <QLabel>

#include "../buttons/menubutton.h"
#include "../../../palette.h"

namespace PIPKA::UI {

CreateDialog::CreateDialog(QWidget *parent)
{
    using namespace Palette;
    setFixedSize(256, 180);
    // setWindowTitle("Create new Image");
    setWindowFlags(Qt::FramelessWindowHint);
    setFont(MENUFONT);
    setStyleSheet(QString(
        "QDialog { background-color: #%1; color: #%2; }"
        "QLabel { color: #%2; font: bold 14px; }"
        "QLineEdit { background-color: #%3; color: #%2; border: 1px solid #%3; padding: 2px; border-radius: 10px; }"
        "QLineEdit:hover { background-color: #%4; border: 1px solid #%4; }"
        "QPushButton:hover { background-color: #%4; }"
    )
    .arg(BASE.rgb() & 0xffffff, 6, 16, QLatin1Char('0'))
    .arg(WHITE.rgb() & 0xffffff, 6, 16, QLatin1Char('0'))
    .arg(NON_ACTIVE.rgb() & 0xffffff, 6, 16, QLatin1Char('0'))
    // .arg(DEFAULT.rgb() & 0xffffff, 6, 16, QLatin1Char('0'))
    .arg(NON_ACTIVE_ON_HOVER.rgb() & 0xffffff, 6, 16, QLatin1Char('0')));

    auto *layout = new QVBoxLayout(this);

    // Width input
    auto *widthLayout = new QHBoxLayout();
    widthLayout->addWidget(new QLabel("Width:"));
    widthInput = new QLineEdit();
    widthInput->setValidator(new QIntValidator(0, 10000, this));
    widthLayout->addWidget(widthInput);
    layout->addLayout(widthLayout);

    // Height input
    auto *heightLayout = new QHBoxLayout();
    heightLayout->addWidget(new QLabel("Height:"));
    heightInput = new QLineEdit();
    heightInput->setValidator(new QIntValidator(0, 10000, this));
    heightLayout->addWidget(heightInput);
    layout->addLayout(heightLayout);

    // Buttons
    auto *buttonLayout = new QVBoxLayout();
    auto *cancelButton = new MenuButton(230, 30, 10, "Cancel");
    auto *createButton = new MenuButton(230, 30, 10, "Create");
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(createButton);
    layout->addLayout(buttonLayout);

    connect(cancelButton, &MenuButton::pressed, this, &QDialog::reject);
    connect(createButton, &MenuButton::pressed, this, &QDialog::accept);
}
}
