#include "criticpathform.h"
#include "ui_criticpathform.h"

CriticPathForm::CriticPathForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CriticPathForm)
{
    ui->setupUi(this);

    auto headerTitles = QStringList();
    headerTitles.append("Atividade");
    headerTitles.append("Duração");
    headerTitles.append("Precedente");
    ui->tableWidget->setHorizontalHeaderLabels(headerTitles);
}

CriticPathForm::~CriticPathForm()
{
    delete ui;
}

void CriticPathForm::on_btnAddRow_clicked()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
}

void CriticPathForm::on_btnConfirm_clicked()
{

}
