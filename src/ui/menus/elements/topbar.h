#ifndef TOPBAR_H
#define TOPBAR_H
#include <QWidget>

namespace PIPKA::UI
{

class TopBar : public QWidget {
    Q_OBJECT
public:
    explicit TopBar(QWidget* parent = nullptr);

signals:
    void hideMenu();
    void save();
    void changeMenu();

private:
    void initUI();

private:
    QPixmap m_changeMenuPixmap{":/menu_burger.png"};
    QPixmap m_savePixmap{":/save.png"};
    QPixmap m_hideMenuPixmap{":/hide_menu.png"};

};

}

#endif //TOPBAR_H
