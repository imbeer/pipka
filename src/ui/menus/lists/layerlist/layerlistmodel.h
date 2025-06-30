#ifndef LAYERLISTMODEL_H
#define LAYERLISTMODEL_H

#include <QAbstractListModel>
#include <QObject>

#include "../../../../control/controller.h"

namespace PIPKA::UI {

class LayerListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit LayerListModel(
        const std::shared_ptr<CONTROL::Controller> &controller,
        QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    void onImageChanged();
    void onAdded(int index);

private:
    std::shared_ptr<IMAGE::Image> m_image;
    const std::shared_ptr<CONTROL::Controller> m_controller;
};

}

#endif // LAYERLISTMODEL_H
