#include "deploypage.h"
#include "ui_deploypage.h"
#include <QMessageBox>
#include "listviewdelegate.h"

DeployPage::DeployPage(CppManager * cpp, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeployPage)
{
    ui->setupUi(this);
    m_cpp = cpp;
    model = new ListModel();
    ui->tableView->setModel(model);
    delegate = new ListViewDelegate();
    ui->tableView->setItemDelegate(delegate);
    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableView->setColumnWidth(1, 40);
    connect(ui->tableView, &QTableView::clicked, this, &DeployPage::clicked);

    connect(ui->checkBox, &QCheckBox::stateChanged, this, &DeployPage::checkChanged);
    connect(ui->deoply, &QPushButton::clicked, this, &DeployPage::deployClicked);
}

void DeployPage::clicked(QModelIndex i){
    if(!ui->tableView->isEnabled()){
        return;
    }

    if(i.column() == 1){
        bool isChecked = model->data(i).toBool();
        model->setData(i, !isChecked);
    }
}

void DeployPage::deployClicked(){
    emit deploy(model->getSelectedList(!ui->tableView->isEnabled()));
}

void DeployPage::buildFinished(){
    model->setSource(m_cpp->cppLibraries());
}

void DeployPage::checkChanged(int e){
    ui->tableView->setEnabled(!e);
}

DeployPage::~DeployPage()
{
    delete delegate;
    delete model;
    delete ui;
}
