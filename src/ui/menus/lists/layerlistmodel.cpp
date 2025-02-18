#include "layerlistmodel.h"

namespace PIPKA::UI {

LayerListModel::LayerListModel(
    const std::shared_ptr<CONTROL::Controller> &controller,
    QObject *parent)
    : QAbstractListModel(parent)
{
    m_image = controller->getImage();

    connect(m_image.get(), &PIPKA::IMAGE::Image::layerAdded,
            this, &LayerListModel::onLayerAdded);
}

int LayerListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0; // handles only top level items
    return m_image->layerSize();
}

QVariant LayerListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_image->layerSize())
        return {};
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return m_image->layers()[index.row()]->name();
    return {};
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

void LayerListModel::onLayerAdded(const int index) {
    beginInsertRows(QModelIndex(), index, index);
    endInsertRows();
}

}
