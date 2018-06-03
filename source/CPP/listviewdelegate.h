#ifndef LISTVIEWDELEGATE_H
#define LISTVIEWDELEGATE_H

#include <QItemDelegate>

class ListViewDelegate : public QItemDelegate
{
public:
    ListViewDelegate();

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // LISTVIEWDELEGATE_H
