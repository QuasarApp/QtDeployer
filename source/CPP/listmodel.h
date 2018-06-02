#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QStandardItemModel>

class ListModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit ListModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void setSource(const QStringList &source);

    QStringList getSelectedList() const;

private:

    QList<QPair<QString, bool>> source;
};

#endif // LISTMODEL_H
