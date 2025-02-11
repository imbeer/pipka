#ifndef LAYERLIST_H
#define LAYERLIST_H

#include "toollist.h"

namespace PIPKA::UI {

class LayerListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit LayerListModel(
        std::shared_ptr<PIPKA::IMAGE::Image> image,
        QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    std::shared_ptr<PIPKA::IMAGE::Image> m_image;
};


class LayerList : public ToolList
{
    Q_OBJECT
public:
    explicit LayerList(
        std::shared_ptr<PIPKA::CONTROL::Controller> &m_controller,
        const int &w = 248, const int &h = 500,
        QWidget *parent = nullptr);

private slots:
    void onItemSelected(const QItemSelection &selected, const QItemSelection &) override;
    void onLayerAdded(const int &index);

private:
    QStringList m_itemList;
};

}

#endif // LAYERLIST_H
