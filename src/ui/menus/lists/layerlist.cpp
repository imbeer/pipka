#include "layerlist.h"

namespace PIPKA::UI {

LayerList::LayerList(
    std::shared_ptr<PIPKA::CONTROL::Controller> &controller,
    const int &w, const int &h,
    QWidget *parent)
    : ToolList<LayerListModel, LayerItemDelegate>(controller, w, h, parent)
{
    connect(m_listView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &LayerList::onItemSelected);
}

void LayerList::onItemSelected(const QItemSelection &selected, const QItemSelection &) const
{
    if (!selected.indexes().isEmpty()) {
        // QString selectedItem = m_model->data(selected.indexes().first(), Qt::DisplayRole).toString();
        m_controller->setActiveLayerIndex(selected.indexes().first().row());
    }
}

// void LayerList::onLayerAdded(const int &index)
// {
    // const auto layer = m_controller->getImage()->layers().at(index);
    // m_model.on
    // update();
// }

}
