#ifndef TOOLLIST_H
#define TOOLLIST_H

#include <type_traits>
#include <QListView>
#include <QWidget>
#include <QVBoxLayout>

#include "scrollbar.h"
#include "../../../control/controller.h"

namespace PIPKA::UI
{

template<typename Model, typename Delegate>
class ToolList : public QWidget
{
    // static_assert(
    //     std::is_base_of_v<QAbstractItemModel, Model>,
    //     "Model is not a child class of QAbstractItemModel");
    // static_assert(
    //     std::is_base_of_v<QAbstractItemDelegate, Delegate>,
    //     "Delegate is not a child class of QAbstractItemDelegate");

public:
    explicit ToolList(
        std::shared_ptr<CONTROL::Controller> controller,
        const int &w = 248, const int &h = 500,
        QWidget *parent = nullptr) : QWidget(parent)
    {
        m_controller = controller;
        m_listView = new QListView(this);
        m_model = new Model(controller, this);
        m_delegate = new Delegate(this);
        setMinimumSize(w, h);
        initUi();
    }

private:
    void initUi()
    {
        m_listView->setModel(m_model);
        m_listView->setItemDelegate(m_delegate);
        m_listView->setStyleSheet("QListView { background: transparent; }");
        m_listView->setContentsMargins(0, 0, 0, 0);
        m_listView->setSpacing(0);

        m_listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_listView->setVerticalScrollBar(new ScrollBar(Qt::Vertical, m_listView));
        m_listView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        m_listView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        m_listView->setLayoutDirection(Qt::RightToLeft);
        // m_listView->setSpacing(0);
        // Layout
        auto *layout = new QVBoxLayout(this);
        layout->addWidget(m_listView);
        setLayout(layout);
    }
protected:

    virtual void onItemSelected(const QItemSelection &selected, const QItemSelection &itemSelection) const = 0;

protected:
    std::shared_ptr<CONTROL::Controller> m_controller;
    QListView *m_listView;
    Model *m_model;
    Delegate *m_delegate;
};
}
#endif // TOOLLIST_H
