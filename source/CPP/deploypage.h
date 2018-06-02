#ifndef DEPLOYPAGE_H
#define DEPLOYPAGE_H

#include <QWidget>
#include "listmodel.h"
#include "mainmanager.h"
#include "cppmanager.h"

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

private slots:
    void deployClicked();
    void checkChanged(int);

signals:
    void deploy(QStringList);
};

#endif // DEPLOYPAGE_H
