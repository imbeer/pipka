#ifndef LAYERLIST_H
#define LAYERLIST_H

#include "layeritemdelegate.h"
#include "layerlistmodel.h"
#include "toollist.h"

namespace PIPKA::UI {
class LayerList : public ToolList<LayerListModel, LayerItemDelegate>
{
    Q_OBJECT
public:
    explicit LayerList(
        std::shared_ptr<PIPKA::CONTROL::Controller> &m_controller,
        const int &w = 248, const int &h = 500,
        QWidget *parent = nullptr);

private slots:
    void onItemSelected(const QItemSelection &selected, const QItemSelection &) const;
    // void onLayerAdded(const int &index);

};

}

#endif // LAYERLIST_H
