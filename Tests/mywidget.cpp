#include "QWidgetAction"
#include "mywidget.h"
#include "ui_mywidget.h"
#include "QMessageBox"

#include <QStandardItemModel>
#include <QTreeWidgetItem>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButton_2_clicked()
{
    QMessageBox::information(this, "Debug", "Add item");

}

void MyWidget::on_pushButton_clicked()
{
    QMessageBox::information(this, "Debug", "Add vertice");
    ui->lblMatrix->setText("   1   2   3   4\n"
                           "1 [0] [0] [0] [0]\n"
                           "2 [0] [0] [0] [0]\n"
                           "3 [0] [0] [0] [0]\n"
                           "4 [0] [0] [0] [0]");
    ui->lblVector->setText("[[1]] -> [2] -> [3]\n"
                           "[[2]] -> [3] -> [1]\n"
                           "[[3]] -> [1]\n");
}

void MyWidget::on_pushButton_4_clicked()
{
    QMessageBox::information(this, "Debug", "Add aresta");
}

void MyWidget::on_pushButton_5_clicked()
{
    QMessageBox::information(this, "Ajuda", "Você pode adicionar a quantidade que quiser de arestas.\n\n"
                                            "Ex.:\n"
                                            "Para adicionar 1: 1,2\n"
                                            "Para adicionar multiplas con.: 1,2/2,3/2,4/1,4\n\n"
                                            "Caso você seleciona a opção direcional, as conexões"
                                            "serão automaticamente direcionadas.");
}
