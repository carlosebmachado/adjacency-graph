#include "criticpathform.h"
#include "ui_criticpathform.h"
#include "graph.hpp"

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
    auto activities = std::vector<std::string>();
    auto durations = std::vector<int>();
    auto previous = std::vector<std::string>();
    size_t rowCount = ui->tableWidget->rowCount();
    for(size_t i = 0; i < rowCount; i++){
        activities.push_back(ui->tableWidget->model()->index(i, 0).data().toString().toStdString());
        durations.push_back(ui->tableWidget->model()->index(i, 1).data().toInt());
        previous.push_back(ui->tableWidget->model()->index(i, 2).data().toString().toStdString());
        //std::cout << ui->tableWidget->model()->index(i, 2).data().toString().toStdString();
    }
    auto graph = Graph::criticalPathGraph(activities, durations, previous);
    //auto criticalPath = Graph::criticalPath(graph);

    // TODO: Mostrar dados...
}
