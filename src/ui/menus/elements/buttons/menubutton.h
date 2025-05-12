#ifndef MENUBUTTON_H
#define MENUBUTTON_H
#include <qstyleoption.h>
#include <QWidget>

namespace PIPKA::UI
{

class MenuButton : public QWidget {
    Q_OBJECT
public:
    MenuButton(
        int width,
        int height,
        int radius,
        const QString &text,
        QWidget* parent = nullptr);

    signals:
        void pressed();

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    const int m_radius;
    const QString m_text;
};

}
#endif //MENUBUTTON_H
