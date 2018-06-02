#include "listmodel.h"

ListModel::ListModel(QObject *parent)
    : QStandardItemModel(parent)
{

}

QVariant ListModel::headerData(int section, Qt::Orientation orientation, int) const
{
    if(orientation == Qt::Vertical){
        switch (section) {
        case 0:
            return tr("lib Path");
        case 1:
            return tr("is Deploy");
        default:
            return QVariant();
            break;
        }
    }
    return QVariant();
}

int ListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return source.size();
}

QVariant ListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole){
        switch (index.column()) {
        case 0: return source[index.row()].first;
        case 1: return source[index.row()].second;
            break;
        default:
            return QVariant();
        }
    }

    return QStandardItemModel::data(index, role);
}

bool ListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.column() != 1){
        return false;
    }

    if (data(index, role) != value) {
        source[index.row()].second = value.toBool();
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags ListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    if (index.column() == 1){
        return Qt::ItemIsSelectable;
    }

    return Qt::NoItemFlags; // FIXME: Implement me!
}

void ListModel::setSource(const QStringList &_source){

    beginResetModel();

    source.clear();
    for(const QString &i : _source){
        source.push_back(QPair<QString, bool>(i, false));
    }
    endResetModel();
}

QStringList ListModel::getSelectedList()const {
    QStringList list;

    for (const QPair<QString, bool> &p: source){
        if(p.second){
            list.push_back(p.first);
        }
    }

    return list;
}
