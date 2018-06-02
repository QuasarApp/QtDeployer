#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(MainManager * mainManager, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    _mainManager = mainManager;
    ui->setupUi(this);

    buidlpage = new BuildPage(this);
    deployPage = new DeployPage(_mainManager->getCpp() ,this);

    ui->stackedWidget->addWidget(buidlpage);
    ui->stackedWidget->addWidget(deployPage);

    ui->stackedWidget->setCurrentIndex(0);


    connect(buidlpage, SIGNAL(build(QString,QString)), _mainManager, SLOT(prepare(QString,QString)));
    connect(_mainManager->getBuild(), SIGNAL(logChanged(QString)), buidlpage, SLOT(log(QString)));
    connect(_mainManager->getBuild(), SIGNAL(finished()), this, SLOT(buidlFinisfed()));
    connect(_mainManager, SIGNAL(stateChanged(int)), this, SLOT(stateChanged(int)));

    connect(deployPage,SIGNAL(deploy(QStringList)), _mainManager, SLOT(deploy(QStringList)));
}

void MainWindow::buidlFinisfed(){
    ui->stackedWidget->setCurrentIndex(1);
    deployPage->buildFinished();
}

void MainWindow::stateChanged(int state){
    if(state == 2){
        QMessageBox::information(this, tr("deploy finished"), tr("programm has been deply into release folder"));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
