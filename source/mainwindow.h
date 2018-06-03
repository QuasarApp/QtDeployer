#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CPP/mainmanager.h"
#include "CPP/buildpage.h"
#include "CPP/deploypage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    MainManager *_mainManager;
    BuildPage *buidlpage;
    DeployPage *deployPage;

    void initMenu();

private slots:
    void buidlFinisfed();
    void stateChanged(int);
    void newDeploy();
    void about();
public:
    explicit MainWindow(MainManager * mainManager, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
