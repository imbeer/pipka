#include "brushlist.h"

#include "../../../../control/repository/brushrepository.h"

namespace PIPKA::UI
{

BrushList::BrushList(
    const std::shared_ptr<CONTROL::Controller> &controller,
    const int &w, const int &h,
    QWidget *parent) :
    ToolList(controller, w, h, parent)
{
    connect(m_listView->selectionModel(), &QItemSelectionModel::selectionChanged,
        this, &BrushList::onItemSelected);
    // connect(m_delegate, &ListItemDelegate::buttonClicked,
        // this, &BrushList::onLayerHide);
    m_listView->selectionModel()->setCurrentIndex(m_model->index(0, 0), QItemSelectionModel::Select);
}

void BrushList::onItemSelected(const QItemSelection &selected, const QItemSelection &itemSelection) const
{
    if (!selected.indexes().isEmpty()) {
        CONTROL::TOOLS::BrushRepository::instance()->selectBrush(selected.indexes().first().row());
    }
}

}
