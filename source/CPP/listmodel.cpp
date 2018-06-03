#include "listmodel.h"

ListModel::ListModel(QObject *parent)
    : QStandardItemModel(parent)
{
    setColumnCount(2);
    this->setHorizontalHeaderLabels(QStringList()<<tr("path")<<tr("add"));
}

QVariant ListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::CheckStateRole && index.column() == 1){
        if (source[index.row()].second)
            return Qt::Checked;
        else
            return Qt::Unchecked;
    }

    if(role == Qt::EditRole && index.column() == 1){
        return source[index.row()].second;
    }


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

    if (data(index, role) != value)
    {
        source[index.row()].second = value.toBool();
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

void ListModel::setSource(const QStringList &_source){

    source.clear();
    for(const QString &i : _source){
        source.push_back(QPair<QString, bool>(i, false));
    }

    this->setRowCount(source.count());

}

QStringList ListModel::getSelectedList(bool all)const {
    QStringList list;

    for (const QPair<QString, bool> &p: source){
        if(p.second || all){
            list.push_back(p.first);
        }
    }

    return list;
}
