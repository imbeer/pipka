#include "layerlist.h"

namespace PIPKA::UI {

LayerList::LayerList(
    std::shared_ptr<CONTROL::Controller> controller,
    const int &w, const int &h,
    QWidget *parent)
    : ToolList(controller, w, h, parent)
{
    connect(m_listView->selectionModel(), &QItemSelectionModel::selectionChanged,
        this, &LayerList::onItemSelected);
    connect(m_delegate, &LayerItemDelegate::hideButtonClicked,
        this, &LayerList::onLayerHide);
}

void LayerList::onItemSelected(const QItemSelection &selected, const QItemSelection &itemSelection) const
{
    if (!selected.indexes().isEmpty()) {
        // QString selectedItem = m_model->data(selected.indexes().first(), Qt::DisplayRole).toString();
        m_controller->setActiveLayerIndex(selected.indexes().first().row());
    }
}

void LayerList::onLayerHide(const QModelIndex &index) const
{
    m_controller->getImage()->layers().at(index.row())->flipVisible();
}

// void LayerList::onLayerAdded(const int &index)
// {
    // const auto layer = m_controller->getImage()->layers().at(index);
    // m_model.on
    // update();
// }

}
