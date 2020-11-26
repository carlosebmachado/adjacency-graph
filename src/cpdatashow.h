#ifndef CPDATASHOW_H
#define CPDATASHOW_H

#include "graph.hpp"
#include <QMainWindow>

namespace Ui {
class CPDataShow;
}

class CPDataShow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CPDataShow(QWidget *parent = nullptr);
    ~CPDataShow();

public:
    void addData(Graph, std::vector<std::string>);

private:
    Ui::CPDataShow *ui;
};

#endif // CPDATASHOW_H
