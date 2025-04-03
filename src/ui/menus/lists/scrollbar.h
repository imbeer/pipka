#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include <QScrollBar>

namespace PIPKA::UI
{

class ScrollBar : public QScrollBar {
    Q_OBJECT

public:
    explicit ScrollBar(
        Qt::Orientation orientation,
        QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;
};

}

#endif //SCROLLBAR_H
