#ifndef BRUSHLISTMODEL_H
#define BRUSHLISTMODEL_H

#include <QAbstractListModel>
#include "../../../../control/controller.h"

namespace PIPKA::UI {

class BrushListModel : public QAbstractListModel {
    Q_OBJECT
public:
    // explicit BrushListModel(QObject *parent = nullptr);
    explicit BrushListModel(
        const std::shared_ptr<CONTROL::Controller> &controller,
        QObject *parent);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    void onAdded(int index);
};

}

#endif //BRUSHLISTMODEL_H
