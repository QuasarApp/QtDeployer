#include "listviewdelegate.h"
#include <QCheckBox>
#include <QPainter>

ListViewDelegate::ListViewDelegate()
{

}

void ListViewDelegate::paint(QPainter *painter,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) const{


    if (index.column() == 1)
    {
        QWidget *w = dynamic_cast<QWidget *>(painter->device());
        if (w)
        {
            QItemDelegate::drawBackground( painter, option, index );
            QItemDelegate::drawCheck( painter, option, option.rect, index.data(Qt::EditRole).toBool() ? Qt::Checked : Qt::Unchecked );
            drawFocus(painter, option, option.rect);
        }
    } else {
        QItemDelegate::paint(painter, option, index);
    }
}

QWidget* ListViewDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const{

    return QItemDelegate::createEditor(parent, option, index);
}


