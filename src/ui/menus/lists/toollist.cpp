#include "toollist.h"

#include "layeritemdelegate.h"
#include "layerlistmodel.h"

#include <QVBoxLayout>
#include <QPainter>
#include <QPainterPath>

namespace PIPKA::UI {

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

template class ToolList<LayerListModel, LayerItemDelegate>;

}
