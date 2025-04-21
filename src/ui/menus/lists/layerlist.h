#ifndef LAYERLIST_H
#define LAYERLIST_H

#include "listitemdelegate.h"
#include "layerlistmodel.h"
#include "toollist.h"

namespace PIPKA::UI
{

class LayerList : public ToolList<LayerListModel, ListItemDelegate>
{
    Q_OBJECT
public:
    explicit LayerList(
        std::shared_ptr<CONTROL::Controller> m_controller,
        const int &w = 248, const int &h = 500,
        QWidget *parent = nullptr);

private slots:
    void onItemSelected(const QItemSelection &selected, const QItemSelection &itemSelection) const override;
    void onLayerHide(const QModelIndex& index) const;
    // void onAdded(const int &index);

};

}

#endif // LAYERLIST_H
