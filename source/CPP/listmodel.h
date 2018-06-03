#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QStandardItemModel>

class ListModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit ListModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    void setSource(const QStringList &source);

    QStringList getSelectedList(bool all) const;

private:

    QList<QPair<QString, bool>> source;
};

#endif // LISTMODEL_H
