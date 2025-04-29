#ifndef ICONBUTTON_H
#define ICONBUTTON_H
#include <QWidget>

namespace PIPKA::UI
{

class IconButton : public QWidget {
    Q_OBJECT
public:
    IconButton(
        int width,
        int height,
        int iconWidth,
        int iconHeight,
        const QPixmap &icon,
        QWidget* parent = nullptr);

signals:
    void pressed();

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QPixmap m_icon;
    const int m_iconWidth;
    const int m_iconHeight;

};

}

#endif //ICONBUTTON_H
