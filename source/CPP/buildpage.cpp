#include "buildpage.h"
#include "ui_buildpage.h"
#include <QFileDialog>


BuildPage::BuildPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BuildPage)
{
    ui->setupUi(this);

    connect(ui->chooseProjectPath, &QPushButton::clicked, this, &BuildPage::chooseProjectDir);
    connect(ui->chooseQtBuildButton, &QPushButton::clicked, this, &BuildPage::chooseQtDir);
    connect(ui->build, &QPushButton::clicked, this, &BuildPage::buildClick);
    connect(ui->pathQtBuild, &QLineEdit::textChanged, this, &BuildPage::chooseChanged);
    connect(ui->projectPath, &QLineEdit::textChanged, this, &BuildPage::chooseChanged);

}

void BuildPage::log(QString log){
    ui->consloleLog->appendPlainText(log);
}

void BuildPage::checkPathes(){
    QString QtBuild = ui->pathQtBuild->text();
    QString Project = ui->projectPath->text();

    bool allGood = true;

    if(!QFile::exists(QtBuild)){
        allGood = false;
        ui->pathQtBuild->setStyleSheet("QLineEdit { background-color: red }");
    }else {

        ui->pathQtBuild->setStyleSheet("QLineEdit { background-color: '#41cd71' }");
    }

    if(!QFile::exists(Project)){
        allGood = false;
        ui->projectPath->setStyleSheet("QLineEdit { background-color: red }");
    }else {
        ui->projectPath->setStyleSheet("QLineEdit { background-color: '#41cd71' }");
    }

    ui->build->setEnabled(allGood);

}

void BuildPage::chooseQtDir(){
    QString _OutputFolder = QFileDialog::getExistingDirectory(this, (tr("Selectt QT Folder")), QDir::homePath());
    ui->pathQtBuild->setText(_OutputFolder);
}


void BuildPage::chooseProjectDir(){
    QString _OutputFolder = QFileDialog::getExistingDirectory(this, tr("Select project Folder"), QDir::currentPath());
    ui->projectPath->setText(_OutputFolder);
}

void BuildPage::buildClick(){
    emit build(ui->pathQtBuild->text(), ui->projectPath->text());
}

void BuildPage::chooseChanged(QString) {
    checkPathes();
}

BuildPage::~BuildPage()
{
    delete ui;
}
