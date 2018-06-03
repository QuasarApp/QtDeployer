#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "CPP/about.h"

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

    initMenu();

    connect(buidlpage, SIGNAL(build(QString,QString)), _mainManager, SLOT(prepare(QString,QString)));
    connect(_mainManager->getBuild(), SIGNAL(logChanged(QString)), buidlpage, SLOT(log(QString)));
    connect(_mainManager->getBuild(), SIGNAL(finished()), this, SLOT(buidlFinisfed()));
    connect(_mainManager, SIGNAL(stateChanged(int)), this, SLOT(stateChanged(int)));

    connect(deployPage,SIGNAL(deploy(QStringList)), _mainManager, SLOT(deploy(QStringList)));
}

void MainWindow::newDeploy(){
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::initMenu(){

    QMenu *file = new QMenu(tr("Qt-Deployer"));

    QAction *deploy = new QAction(tr("new deploy"), this);
    connect(deploy, SIGNAL(triggered(bool)),SLOT(newDeploy()));
    file->addAction(deploy);

    QAction *about = new QAction(tr("about"), this);
    connect(about, SIGNAL(triggered(bool)),SLOT(about()));
    file->addAction(about);

    ui->menubar->addMenu(file);

}

void MainWindow::about(){
    (new About())->show();
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
