#include "criticpathform.h"
#include "ui_criticpathform.h"
#include "graph.hpp"
#include "cpdatashow.h"

CriticPathForm::CriticPathForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CriticPathForm)
{
    ui->setupUi(this);

    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << tr("Atividade") << tr("Duração") << tr("Precedente"));
}

CriticPathForm::~CriticPathForm()
{
    delete ui;
}

void CriticPathForm::on_btnAddRow_clicked()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
}

void CriticPathForm::on_btnRemoveRow_clicked()
{
    ui->tableWidget->removeRow(ui->tableWidget->rowCount() - 1);
}

void CriticPathForm::on_btnConfirm_clicked()
{
    auto activities = std::vector<std::string>();
    auto durations = std::vector<int>();
    auto previous = std::vector<std::string>();
    size_t rowCount = ui->tableWidget->rowCount();
    for(size_t i = 0; i < rowCount; i++){
        activities.push_back(ui->tableWidget->model()->index(i, 0).data().toString().toStdString());
        durations.push_back(ui->tableWidget->model()->index(i, 1).data().toInt());
        //auto p = ui->tableWidget->model()->index(i, 2).data().toString().toStdString();
        //if(p == "-") p = "";
        //previous.push_back(p);
        previous.push_back(ui->tableWidget->model()->index(i, 2).data().toString().toStdString());
        //std::cout << ui->tableWidget->model()->index(i, 2).data().toString().toStdString();
    }
    // TODO: VALIDAR SE PRECEDENTE NÃO É IGUAL A ATIVIDADE
    auto graph = Graph::criticalPathGraph(activities, durations, previous);

    auto criticalPath = Graph::criticalPath(graph);

//    graph = Graph("teste");
//    criticalPath = std::vector<std::string>();
//    criticalPath.push_back("Início");
//    for(int i = 0; i < 9; i++){
//        graph.addVertex(new CriticVertex("tarefa " + std::to_string(i), 0, 0, 0, 0, 0, 0));
//        criticalPath.push_back("tarefa " + std::to_string(i));
//    }
//    criticalPath.push_back("Fim");

    auto dataForm = new CPDataShow();
    dataForm->addData(*graph, criticalPath);
    dataForm->show();
}
