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

    connect(m_controller->getImage().get(), &PIPKA::IMAGE::Image::layerAdded,
            this, &LayerList::onLayerAdded);
}

void LayerList::onItemSelected(const QItemSelection &selected, const QItemSelection &)
{
    if (!selected.indexes().isEmpty()) {
        // QString selectedItem = m_model->data(selected.indexes().first(), Qt::DisplayRole).toString();
        m_controller->setActiveLayerIndex(selected.indexes().first().row());
    }
}

void LayerList::onLayerAdded(const int &index)
{
    // const auto layer = m_controller->getImage()->layers().at(index);
    update();
}

}
