#include "brushlistmodel.h"
#include "../../../control/repository/brushrepository.h"

namespace PIPKA::UI {

using CONTROL::TOOLS::BrushRepository;

// BrushListModel::BrushListModel(QObject *parent) :
// QAbstractListModel(parent)
// {
//     connect(BrushRepository::instance(), &BrushRepository::brushAdded,
//             this, &BrushListModel::onAdded);
// }

BrushListModel::BrushListModel(
    const std::shared_ptr<CONTROL::Controller> &controller,
    QObject *parent) :
    QAbstractListModel(parent)
{
    connect(BrushRepository::instance(), &BrushRepository::brushAdded,
            this, &BrushListModel::onAdded);
}

int BrushListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return BrushRepository::instance()->storage().size();
}

QVariant BrushListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= BrushRepository::instance()->storage().size())
        return {};
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        QVariantMap dataMap;
        dataMap["text"] = BrushRepository::instance()->storage()[index.row()]->name();
        return dataMap;
    }
    return {};
}

bool BrushListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return false;
}

Qt::ItemFlags BrushListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

void BrushListModel::onAdded(const int index)
{
    beginInsertRows(QModelIndex(), index, index);
    endInsertRows();
}

}
