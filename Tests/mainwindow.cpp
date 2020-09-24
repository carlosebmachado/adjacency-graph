#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mywidget.h"

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


void MainWindow::on_actionNovo_triggered()
{
    MyWidget* nt = new MyWidget();
    ui->tabWidget->addTab(nt, "untitled");
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}
