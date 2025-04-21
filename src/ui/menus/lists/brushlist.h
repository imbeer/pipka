#ifndef BRUSHLIST_H
#define BRUSHLIST_H
#include "brushitemdelegate.h"
#include "brushlistmodel.h"
#include "toollist.h"

namespace PIPKA::UI
{

class BrushList : public ToolList<BrushListModel, BrushItemDelegate> {

public:
    BrushList(
        const std::shared_ptr<CONTROL::Controller> &controller,
        const int &w, const int &h,
        QWidget *parent);

private slots:
    void onItemSelected(const QItemSelection &selected, const QItemSelection &itemSelection) const override;
};

}

#endif //BRUSHLIST_H
