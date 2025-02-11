#include "toollist.h"

#include <QVBoxLayout>
#include <QPainter>
#include <QPainterPath>

namespace PIPKA::UI {

ToolListItem::ToolListItem(QObject *parent)
    : QStyledItemDelegate(parent) {}

void ToolListItem::paint(
    QPainter *painter,
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    QString text = index.data(Qt::DisplayRole).toString();
    auto marginedRect = option.rect.adjusted(0, 5, 0, -5);
    painter->setPen(Qt::NoPen);

    QPainterPath path;
    path.addRoundedRect(marginedRect, 10, 10);

    if (option.state & QStyle::State_Selected) {
        // painter->fillPath(path, QColor(0xFF444444));
        QLinearGradient gradient(option.rect.topLeft(), option.rect.topRight());
        gradient.setColorAt(0.0, QColor(0x444444));
        gradient.setColorAt(1.0, QColor(0x2C2C2C));
        // painter->setBrush(gradient);
        painter->fillPath(path, gradient);
    } else {
        painter->fillPath(path, QColor(0xFF2C2C2C));
        // painter->setBrush(QColor(0xFF444444));
        // painter->drawRoundedRect(marginedRect, 10, 10);
    }

    painter->setPen(QColor(0xFFFFFFFF));
    painter->setFont(QFont("Arial", 12, QFont::Bold));
    painter->drawText(marginedRect.adjusted(10, 5, -10, -5), Qt::AlignVCenter | Qt::AlignLeft, text);
}

QSize ToolListItem::sizeHint(
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize(235, 40);
}

ToolList::ToolList(
    std::shared_ptr<PIPKA::CONTROL::Controller> &controller,
    const int &w, const int &h,
    QWidget *parent)
    : QWidget{parent}, m_controller(controller)
{
    initUi();
}

void ToolList::initUi()
{
    m_listView = new QListView(this);
    // m_model = new QStringListModel(this);
    m_delegate = new ToolListItem(this);

    // Populate List
    // QStringList itemList;
    // itemList << "Item 1" << "Item 2" << "Item 3" << "Item 4";
    // m_model->setStringList(itemList);

    // Set model to ListView
    // m_listView->setModel(m_model);
    m_listView->setItemDelegate(m_delegate);
    m_listView->setStyleSheet("QListView { background: transparent; }");
    m_listView->setContentsMargins(0, 0, 0, 0);
    m_listView->setSpacing(0);

    // Connect selection signal
    connect(m_listView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &ToolList::onItemSelected);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_listView);
    setLayout(layout);
}

}
