#ifndef DEPLOYPAGE_H
#define DEPLOYPAGE_H

#include <QWidget>
#include "listmodel.h"
#include "mainmanager.h"
#include "cppmanager.h"
#include "listviewdelegate.h"

namespace Ui {
class DeployPage;
}

class DeployPage : public QWidget
{
    Q_OBJECT

public:
    explicit DeployPage(CppManager *cpp ,QWidget *parent = 0);
    void buildFinished();

    ~DeployPage();

private:

    CppManager *m_cpp;
    Ui::DeployPage *ui;
    ListModel *model;
    ListViewDelegate *delegate;

private slots:
    void deployClicked();
    void checkChanged(int);
    void clicked(QModelIndex);

signals:
    void deploy(QStringList);
};

#endif // DEPLOYPAGE_H
