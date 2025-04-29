#ifndef SPLITTER_H
#define SPLITTER_H
#include <QWidget>

namespace PIPKA::UI {

class Splitter : public QWidget {

public:
    Splitter(
        QWidget *parent = nullptr,
        int width = 256, // длина линии
        int height = 52, // margin
        int thickness = 1); // толщина линии


protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_thickness;
};

}

#endif //SPLITTER_H
