#ifndef TOOLLIST_H
#define TOOLLIST_H

#include <type_traits>
#include <QListView>
#include <QWidget>
#include "layeritemdelegate.h"
#include "layerlistmodel.h"

#include <QVBoxLayout>
#include "../../../control/controller.h"

namespace PIPKA::UI {

template <typename Model, typename Delegate>
class ToolList : public QWidget
{
    static_assert(
        std::is_base_of_v<QAbstractItemModel, Model>,
        "Model is not a child class of QAbstractItemModel");
    static_assert(
        std::is_base_of_v<QAbstractItemDelegate, Delegate>,
        "Delegate is not a child class of QAbstractItemDelegate");

    // Q_OBJECT
public:
    explicit ToolList(
        std::shared_ptr<CONTROL::Controller> &controller,
        const int &w = 248, const int &h = 500,
        QWidget *parent = nullptr);

private:
    void initUi();

protected:
    std::shared_ptr<CONTROL::Controller> m_controller;
    QListView *m_listView;
    Model *m_model;
    Delegate *m_delegate;

};




/// IMPLEMENTATION
template <typename Model, typename Delegate>
ToolList<Model, Delegate>::ToolList(
    std::shared_ptr<CONTROL::Controller> &controller,
    const int &w, const int &h,
    QWidget *parent)
    : QWidget{parent}, m_controller(controller)
{
    m_listView = new QListView(this);
    m_model = new Model(controller, this);
    m_delegate = new Delegate(this);
    setBaseSize(w, h);
    initUi();
}

template <typename Model, typename Delegate>
void ToolList<Model, Delegate>::initUi()
{
    m_listView->setModel(m_model);
    m_listView->setItemDelegate(m_delegate);
    m_listView->setStyleSheet("QListView { background: transparent; }");
    m_listView->setContentsMargins(0, 0, 0, 0);
    m_listView->setSpacing(0);

    // Layout
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(m_listView);
    setLayout(layout);
}

}

#endif // TOOLLIST_H
