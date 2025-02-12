#ifndef TOOLLIST_H
#define TOOLLIST_H

#include <type_traits>
#include <QListView>
#include <QWidget>
#include "../../../control/controller.h"

namespace PIPKA::UI {

template <typename Model, typename Delegate>
class ToolList : public QWidget
{
    static_assert(
        std::is_base_of<QAbstractItemModel, Model>::value,
        "Model is not a child class of QAbstractItemModel");
    static_assert(
        std::is_base_of<QAbstractItemDelegate, Delegate>::value,
        "Delegate is not a child class of QAbstractItemDelegate");

    // Q_OBJECT
public:
    explicit ToolList(
        std::shared_ptr<PIPKA::CONTROL::Controller> &controller,
        const int &w = 248, const int &h = 500,
        QWidget *parent = nullptr);

private:
    void initUi();

protected:
    std::shared_ptr<PIPKA::CONTROL::Controller> m_controller;
    QListView *m_listView;
    Model *m_model;
    Delegate *m_delegate;

};

}

#endif // TOOLLIST_H
