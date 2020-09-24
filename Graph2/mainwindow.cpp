#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "graphfile.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}

void MainWindow::on_actionShowHelp_triggered()
{
    QMessageBox::information(this, "Ajuda",
                             "Vértices:\n"
                             "Você pode adicionar um vértice digitando o ID. Caso queira adicionar mais de um por vez "
                             "é possível separá-los com vírgula. Ex.: a,b,c,d\n"
                             "A plotagem não foi implementada ainda.\n\n" /*"e sua posição X e Y. Mas caso "
                                                          "não queira informar as posições, é possível deixá-las em branco.\n\n"*/
                             "Arestas:\n"
                             "Você pode adicionar uma ou mais arestas de cada vez. Por exemplo, caso queira adicionar "
                             "apenas uma você pode digitar apenas os IDs dos vértices separados por vírgula "
                             "(neste caso, os IDs são '1' e '2'). Ex.: 1,2\n"
                             "Para adicionar multiplas arestas, você irá separar cada uma delas por ';'. Ex.: "
                             "1,2/2,3/2,4/1,4\n"
                             "Caso você selecione a opção direcional, as conexões serão automaticamente direcionadas.");
}

void MainWindow::on_actionNew_triggered()
{
    auto newTab = new GraphFile(ui->tabWidget);
    ui->tabWidget->addTab(newTab, "Novo grafo");
    ui->tabWidget->setCurrentIndex(ui->tabWidget->indexOf(newTab));
}

void MainWindow::on_btnNew_clicked()
{
    on_actionNew_triggered();
}

void MainWindow::on_btnShowHelp_clicked()
{
    on_actionShowHelp_triggered();
}

void MainWindow::on_actionLoad_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Abrir Grafo"), "",
                                                    tr("Grafo (*.bps);;Todos os arquivos (*)"));

    if (fileName.isEmpty()) return;

    auto newTab = new GraphFile(ui->tabWidget);
    newTab->open(fileName.toStdString());
    ui->tabWidget->addTab(newTab, newTab->graph.text.c_str());
    ui->tabWidget->setCurrentIndex(ui->tabWidget->indexOf(newTab));
}

void MainWindow::on_btnOpen_clicked()
{
    on_actionLoad_triggered();
}

void MainWindow::on_actionSave_triggered()
{
    auto dt = (QTabWidget*) ui->tabWidget;
    if(dt->tabText(dt->currentIndex()) == "Bem vindo") return;

    auto tab = (GraphFile*) ui->tabWidget->currentWidget();
    if (tab->path == ""){
        on_actionSaveAs_triggered();
    }else{
        tab->save("");
    }
}

void MainWindow::on_actionSaveAs_triggered()
{
    auto dt = (QTabWidget*) ui->tabWidget;
    if(dt->tabText(dt->currentIndex()) == "Bem vindo") return;

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Salvar Grafo"), "",
                                                    tr("Grafo (*.bps);;Todos os arquivos (*)"));

    if (fileName.isEmpty()){
        QMessageBox::warning(this, "Erro", "Nome não pode ser vazio.");
    } else {
        auto tab = (GraphFile*) ui->tabWidget->currentWidget();
        tab->save(fileName.toStdString());
    }
}

void MainWindow::on_actionExit_triggered()
{

}









































