#include "graphfile.h"
#include "ui_graphfile.h"

GraphFile::GraphFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphFile)
{
    ui->setupUi(this);

    // initial configs
    graph = Graph("Novo Grafo");
}

GraphFile::~GraphFile()
{
    delete ui;
}


// buttons
void GraphFile::on_btnAddVertex_clicked()
{
    QString idstr = ui->txtVertexID->text();

    if(idstr == ""){
        QMessageBox::warning(this, "Erro", "ID não pode ser vazio.");
    }

    auto ids = split(idstr.toStdString(), ',');
    for(auto id : ids){
        graph.addVertex(new Vertex(id));
    }

    updateAdjacencyVector();
    updateAdjacencyMatrix();

    ui->txtVertexID->setText("");
    ui->txtVertexID->setFocus();
}

void GraphFile::on_btnRemoveVertex_clicked()
{
    QString idstr = ui->txtVertexID->text();

    if(idstr == ""){
        QMessageBox::warning(this, "Erro", "ID não pode ser vazio.");
    }

    auto ids = split(idstr.toStdString(), ',');
    for(auto id : ids){
        graph.removeVertex(id);
    }

    updateAdjacencyVector();
    updateAdjacencyMatrix();

    ui->txtVertexID->setText("");
    ui->txtVertexID->setFocus();
}

void GraphFile::on_btnAddEdge_clicked()
{
    QString constr = ui->txtEdges->text();
    bool dir = ui->cbDirection->isChecked();

    if(constr == ""){
        QMessageBox::warning(this, "Erro", "ID não pode ser vazio.");
    }

    auto cons = split(constr.toStdString(), ';');
    for(auto con : cons){
        auto ids = split(con, ',');
        graph.addEdge(ids[0], ids[1]);
        if(dir) graph.addEdge(ids[1], ids[0]);
    }

    updateAdjacencyVector();
    updateAdjacencyMatrix();

    ui->txtEdges->setText("");
    ui->txtEdges->setFocus();
}

void GraphFile::on_btnRemoveEdge_clicked()
{
    QString constr = ui->txtEdges->text();
    bool dir = ui->cbDirection->isChecked();

    if(constr == ""){
        QMessageBox::warning(this, "Erro", "ID não pode ser vazio.");
    }

    auto cons = split(constr.toStdString(), ';');
    for(auto con : cons){
        auto ids = split(con, ',');
        graph.removeEdge(ids[0], ids[1]);
        if(dir) graph.removeEdge(ids[1], ids[0]);
    }

    updateAdjacencyVector();
    updateAdjacencyMatrix();

    ui->txtEdges->setText("");
    ui->txtEdges->setFocus();
}

void GraphFile::on_btnDFS_clicked()
{
    QString id = ui->txtSearchID->text();
    if(id == ""){
        QMessageBox::warning(this, "Erro", "ID não pode ser vazio.");
        return;
    }
    QMessageBox::information(this, "DFS", QString(graph.DFS(new Vertex(id.toStdString())).c_str()));
}

void GraphFile::on_btnBFS_clicked()
{
    QString id = ui->txtSearchID->text();
    if(id == ""){
        QMessageBox::warning(this, "Erro", "ID não pode ser vazio.");
        return;
    }
    QMessageBox::information(this, "BFS", QString(graph.BFS(new Vertex(id.toStdString())).c_str()));
}

void GraphFile::on_btnConnected_clicked()
{
    QString title = "Verificação de grafo conexo";
    // verifica se é conexo
    bool isConnected = graph.isConnectivity();
    if(isConnected){
        // caso seja conexo
        QMessageBox::information(this, title, "O grafo é conexo.");
    } else {
        // caso não seja
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, title, "O grafo não é conexo. Deseja identificar os subgrafos fortemente conexos?");
        if (reply == QMessageBox::Yes) {
            // clicou em sim, então roda a função para encontra-los
            std::vector<Graph> graphs = graph.getSubGraphs();
            QString subGraphs = "";
            for(auto sg : graphs){
                subGraphs += "Subgrafo fortemente conexo <";
                subGraphs += sg.text.c_str();
                subGraphs += ">:\n";
                subGraphs += sg.getStrAdjMatrix().c_str();
                subGraphs += "\n\n";
            }
            QMessageBox::information(this, "Subgrafos fortemente conexos", subGraphs);
        }
    }
}


// interface update
void GraphFile::updateAdjacencyVector() {
    ui->lblVector->setText(graph.getStrAdjVector().c_str());
}

void GraphFile::updateAdjacencyMatrix() {
    ui->lblMatrix->setText(graph.getStrAdjMatrix().c_str());
}

void GraphFile::open(std::string path){
    // carrega arquivo bps do disco p/ memoria
    BPS::File* file = BPS::read(path);

    // cada arquivo vai conter somente uma section
    // loop ajdua a verificar se ela existe
    for (auto section : file->findAll()) {
        // cria o grafo
        graph = Graph(section->getName());
        this->path = path;
        plotable = section->exists("xy");

        auto vdata = (BPS::StringData*) section->find("vertices");
        auto edata = (BPS::StringData*) section->find("edges");

        std::string vertices = vdata->getValue();
        std::string edges = edata->getValue();

        // cria os vertices
        auto ids = split(vertices, ',');
        for(auto id : ids){
            graph.addVertex(new Vertex(id));
        }

        // cria as conexoes
        auto cons = split(edges, ';');
        for(auto con : cons){
            auto ids = split(con, ',');
            graph.addEdge(ids[0], ids[1]);
        }
    }

    updateAdjacencyVector();
    updateAdjacencyMatrix();
}

void GraphFile::save(std::string path){
    // arquivo bps
    BPS::File* file = new BPS::File();
    BPS::Section* section = new BPS::Section(graph.text);

    std::string vertices = "";
    std::string edges = "";
    // loop para pegar vertices e conexoes
    for(size_t i = 0; i < graph.vertices.size(); i++){
        for(size_t j = 0; j < graph.vertices[i]->adjacencies.size(); j++){
            // add o vertice
            vertices += graph.vertices[i]->id;
            if(i < graph.vertices.size() - 1) vertices += ",";
            // add a conexao
            edges += graph.vertices[i]->id + "," + graph.vertices[i]->adjacencies[j]->id;
            edges += ";";
        }
    }
    edges = edges.substr(0, edges.size() - 1);
    // salva no aquivo em memoria
    section->add(new BPS::StringData("vertices", vertices));
    section->add(new BPS::StringData("edges", edges));

    file->add(section);

    if(path != ""){
        this->path = path;
        auto dp = split(path, '/');
        auto name = dp[dp.size() - 1];
        section->setName(name);
    }
    // salva no disco
    BPS::write(file, this->path);
}
