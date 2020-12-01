#include "cpdatashow.h"
#include "ui_cpdatashow.h"

#include <QGridLayout>
#include <QLabel>
#include <QTableWidget>

CPDataShow::CPDataShow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CPDataShow)
{
    ui->setupUi(this);
}

CPDataShow::~CPDataShow()
{
    delete ui;
}

void CPDataShow::addData(Graph graph, std::vector<std::string> criticPath){
    auto layout = new QGridLayout();
    size_t vsize = graph.vertices.size();
    size_t cpsize = criticPath.size();
    int r = 1, c = 0, l = (vsize * 0.3333333);

    // critic path
    QString cps = "";
    for(size_t i = 0; i < cpsize; i++){
        cps += criticPath[i].c_str();
        if(i < (cpsize - 1)){
            cps += " -> ";
        }
    }
    layout->addWidget(new QLabel("Caminho crítico: " + cps), 0, 0, 1, l);

    // graph
    for(size_t i = 0; i < vsize; i++){
        // current table
        auto curTable = new QTableWidget();
        curTable->setGeometry(0, 0, 225, 120);
        curTable->setMaximumSize(225, 120);
        curTable->setMinimumSize(225, 120);

        // set rows and cols
        curTable->setColumnCount(3);
        curTable->setColumnWidth(0, 60);
        curTable->setColumnWidth(1, 50);
        curTable->setColumnWidth(2, 90);
        curTable->setRowCount(3);

        // set header titles
        curTable->setHorizontalHeaderLabels(QStringList() << tr("Atividade") << tr("Duração") << tr("Apontamentos"));

        // set data
        auto curVertex = (CriticVertex*)graph.vertices[i];
        // activity
        curTable->setItem(0, 0, new QTableWidgetItem(curVertex->id.c_str()));
        // duration time
        curTable->setItem(0, 1, new QTableWidgetItem(std::to_string(curVertex->duration).c_str()));
        // minGoing
        curTable->setItem(1, 0, new QTableWidgetItem(std::to_string(curVertex->minGoing).c_str()));
        // maxGoing
        curTable->setItem(1, 1, new QTableWidgetItem(std::to_string(curVertex->maxGoing).c_str()));
        // minBack
        curTable->setItem(2, 0, new QTableWidgetItem(std::to_string(curVertex->minBack).c_str()));
        // maxBack
        curTable->setItem(2, 1, new QTableWidgetItem(std::to_string(curVertex->maxBack).c_str()));
        // dayOff
        curTable->setItem(1, 2, new QTableWidgetItem(std::to_string(curVertex->dayOff).c_str()));

        QString appoints = "";
        auto aisize = curVertex->adjacencies.size();
        for(size_t ai = 0; ai < aisize; ai++){
            appoints += curVertex->adjacencies[ai].adjacency->id.c_str();
            if(i < (aisize - 1)){
                appoints += ", ";
            }
        }
        // appoints
        curTable->setItem(0, 2, new QTableWidgetItem(appoints));

        layout->addWidget(curTable, r, c);

        c++;
        if(c > l){
            c = 0;
            r++;
        }
    }
    ui->centralwidget->setLayout(layout);
}
