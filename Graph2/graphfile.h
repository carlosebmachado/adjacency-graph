#ifndef GRAPHFILE_H
#define GRAPHFILE_H

#include <QWidget>

#include "graph.hpp"

namespace Ui {
class GraphFile;
}

class GraphFile : public QWidget
{
    Q_OBJECT

public:
    Graph graph;
    bool plotable = false;
    std::string path = "";

public:
    explicit GraphFile(QWidget *parent = nullptr);
    ~GraphFile();

    void updateAdjacencyVector();
    void updateAdjacencyMatrix();
    void save(std::string);
    void open(std::string);

private slots:
    void on_btnAddVertex_clicked();
    void on_btnRemoveVertex_clicked();
    void on_btnAddEdge_clicked();
    void on_btnRemoveEdge_clicked();
    void on_btnDFS_clicked();
    void on_btnBFS_clicked();

private:
    Ui::GraphFile *ui;
};

#endif // GRAPHFILE_H
