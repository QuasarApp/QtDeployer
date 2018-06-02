#include "deploypage.h"
#include "ui_deploypage.h"
#include <QMessageBox>

DeployPage::DeployPage(CppManager * cpp, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeployPage)
{
    ui->setupUi(this);
    m_cpp = cpp;
    model = new ListModel();
    ui->tableView->setModel(model);
    connect(ui->checkBox, &QCheckBox::stateChanged, this, &DeployPage::checkChanged);
    connect(ui->deoply, &QPushButton::clicked, this, &DeployPage::deployClicked);
}

void DeployPage::deployClicked(){
    emit deploy(model->getSelectedList());
}

void DeployPage::buildFinished(){
    model->setSource(m_cpp->cppLibraries());
}

void DeployPage::checkChanged(int e){
    ui->checkBox->setEnabled(!e);
}

DeployPage::~DeployPage()
{
    delete model;
    delete ui;
}
