#ifndef TOOLLIST_H
#define TOOLLIST_H

#include <QStringListModel>
#include <QListView>
#include <QWidget>
#include <QStyledItemDelegate>
#include "../../control/controller.h"

namespace PIPKA::UI {

class ToolListItem : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ToolListItem(QObject *parent = nullptr);

    void paint(
        QPainter *painter,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const override;
    QSize sizeHint(
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const override;
};


class ToolList : public QWidget
{
    Q_OBJECT
public:
    explicit ToolList(
        std::shared_ptr<PIPKA::CONTROL::Controller> &controller,
        const int &w = 248, const int &h = 500,
        QWidget *parent = nullptr);

private:
    void initUi();

private slots:
    virtual void onItemSelected(const QItemSelection &selected, const QItemSelection &) = 0;

protected:
    std::shared_ptr<PIPKA::CONTROL::Controller> m_controller;
    QListView *m_listView;
    QAbstractListModel *m_model;
    ToolListItem *m_delegate;

};

}

#endif // TOOLLIST_H
