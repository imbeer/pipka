#include "layerlist.h"

namespace PIPKA::UI {

LayerListModel::LayerListModel(
    std::shared_ptr<PIPKA::IMAGE::Image> image,
    QObject *parent)
    : QAbstractListModel(parent)
{
    m_image = image;
}

int LayerListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0; // handles only top level items
    return m_image->layerSize();
}

QVariant LayerListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_image->layerSize())
        return QVariant();
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return m_image->layers()[index.row()]->name();
    return QVariant();
}

bool LayerListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || index.row() >= m_image->layerSize() || role != Qt::EditRole)
        return false;
    m_image->layers()[index.row()]->setName(value.toString());
    emit dataChanged(index, index, {role});
    return true;
}

Qt::ItemFlags LayerListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

LayerList::LayerList(
    std::shared_ptr<PIPKA::CONTROL::Controller> &controller,
    const int &w, const int &h,
    QWidget *parent)
    : ToolList(controller, w, h, parent)
{
    m_model = new LayerListModel(controller->getImage());
    m_listView->setModel(m_model);


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
    const auto layer = m_controller->getImage()->layers().at(index);
    update();
}


}
