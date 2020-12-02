#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <list>
#include <queue>
#include "util.hpp"

#undef INFINITY
#define INFINITY ULLONG_MAX
class Vertex;

class Edge {
public:
    Vertex* adjacency;
    int weight;

    Edge(Vertex* adjacency){
        this->adjacency = adjacency;
    }

    Edge(Vertex* adjacency, int weight){
        this->adjacency = adjacency;
        this->weight = weight;
    }
};

class Vertex {
public:
    std::string id;
    int x, y;
    std::vector<Edge> adjacencies;

    Vertex(std::string id) {
        this->x = 0;
        this->y = 0;
        this->id = id;
        adjacencies = std::vector<Edge>();
    }

    Vertex(int x, int y, std::string id) {
        this->x = x;
        this->y = y;
        this->id = id;
        adjacencies = std::vector<Edge>();
    }
};

class CriticVertex : public Vertex {
public:

    int minGoing;
    int maxGoing;
    int minBack;
    int maxBack;

    int duration;
    int dayOff;

    CriticVertex(std::string id, int x, int y, int minGoing, int maxGoing, int minBack, int maxBack, int duration, int dayOff) : Vertex(x, y, id) {
        this->minGoing = minGoing;
        this->maxGoing = maxGoing;
        this->minBack = minBack;
        this->maxBack = maxBack;
        
        this->duration = duration;
        this->dayOff = dayOff;   
    }

    CriticVertex(std::string id, int minGoing, int maxGoing, int minBack, int maxBack, int duration, int dayOff) : Vertex(id) {
        this->minGoing = minGoing;
        this->maxGoing = maxGoing;
        this->minBack = minBack;
        this->maxBack = maxBack;
        
        this->duration = duration;
        this->dayOff = dayOff;   
    }

    CriticVertex(std::string id, int duration) : Vertex(id) {
        this->minGoing = -1;
        this->maxGoing = -1;
        this->minBack = -1;
        this->maxBack = -1;

        this->duration = duration;
        this->dayOff = -1;
    }

    CriticVertex(std::string id) : Vertex(id) {
        this->minGoing = -1;
        this->maxGoing = -1;
        this->minBack = -1;
        this->maxBack = -1;

        this->duration = -1;
        this->dayOff = -1;
    }

};

class Graph {
public:
    std::string text;
    std::vector<Vertex*> vertices;

    Graph() {
        this->text = "";
        vertices = std::vector<Vertex*>();
    }

    Graph(std::string text) {
        this->text = text;
        vertices = std::vector<Vertex*>();
    }

    Graph(std::string text, std::vector<Vertex*> vertices) {
        this->text = text;
        this->vertices = vertices;
    }

    // Adiciona um novo vertice
    bool addVertex(Vertex* vertex) {
        if (!existis(vertex->id)) {
            vertices.push_back(vertex);
            return true;
        }
        return false;
    }

    // Remove um vertice a partir do id
    bool removeVertex(std::string id) {
        for (size_t i = 0; i < vertices.size(); i++) {
            if (vertices[i]->id == id) {
                vertices.erase(vertices.begin() + i);
                return true;
            }
        }
        return false;
    }

    // Verifica se um vertice existe
    bool existis(std::string id) {
        for (auto v : vertices)
            if (v->id == id) return true;
        return false;
    }

    // adiciona uma nova aresta a partir do id do vertice 1 e do vertice 2 e o peso
    bool addEdge(std::string id1, std::string id2, int weight) {
        for (auto v1 : vertices) {
            if (v1->id == id1) {
                for(auto adjs : v1->adjacencies){
                    if (adjs.adjacency->id == id2) {
                        return false;
                    }
                }
                for (auto v2 : vertices) {
                    if (v2->id == id2) {
                        v1->adjacencies.push_back(Edge(v2, weight));
                        return true;
                    }
                }
            }
        }
        return false;
    }

    // remove uma aresta a partir do id do vertice 1 e do vertice 2
    bool removeEdge(std::string id1, std::string id2) {
        for (auto v1 : vertices) {
            if (v1->id == id1) {
                for (size_t v2 = 0; v2 < v1->adjacencies.size(); v2++) {
                    if (v1->adjacencies[v2].adjacency->id == id2) {
                        v1->adjacencies.erase(v1->adjacencies.begin() + v2);
                        return true;
                    }
                }
            }
        }
        return false;
    }

    // retorna o endereço de memoria do id passado
    Vertex* getVertex(std::string id) {
        for (size_t i = 0; i < vertices.size(); i++) {
            if (vertices[i]->id == id) {
                return vertices[i];
            }
        }
        return nullptr;
    }

    Vertex* getVertex(size_t index) {
        return (Vertex*) vertices[index];
    }

    // retorna o indice de um vertice na lista de adjacencias
    size_t indexOfVertex(std::string id) {
        for (size_t i = 0; i < vertices.size(); i++) {
            if (vertices[i]->id == id) {
                return i;
            }
        }
        return -1;
    }

    // retorna uma string contendo a matrix de adj
    std::string getStrAdjMatrix() {
        int** adjMatrix = getAdjMatrix();
        size_t size = vertices.size();
        std::string str = "";

        // concatena a matriz em uma str junto com o id de cada vertice
        for (size_t i = 0; i < size; i++) {
            str += "     ";
            str += vertices[i]->id.c_str();
        }
        str += "\n";
        for (size_t i = 0; i < size; i++) {
            str += vertices[i]->id.c_str();
            str += " ";
            for (size_t j = 0; j < size; j++) {
                str += " [ ";
                str += std::to_string(adjMatrix[i][j]).c_str();
                str += " ]";
            }
            str += "\n";
        }

        return str;
    }

    // retorna uma string contendo o vetor de ajacencia
    std::string getStrAdjVector() {
        auto adjVector = std::vector<std::vector<std::string>>();
        std::string str = "";
        // cria um vetor de strings (cada linha um vertice)
        for (auto v : vertices) {
            adjVector.push_back(std::vector<std::string>());
            adjVector[adjVector.size() - 1].push_back("([ " + v->id + " ])");
            for (auto a : v->adjacencies) {
                adjVector[adjVector.size() - 1].push_back(" -> [ " + a.adjacency->id + " ]");
            }
        }

        for (auto v : adjVector) {
            for (auto t : v) {
                str += t.c_str();
            }
            str += "\n";
        }

        return str;
    }

    // retorna a lista de adj
    std::vector<Vertex*> getAdjVector(){
        return vertices;
    }

    // retorna a matriz de adj crua
    int** getAdjMatrix() {
        auto matrix = createMatrixOfZeros(vertices.size(), vertices.size());
        for (size_t i = 0; i < vertices.size(); i++) {
            for (size_t j = 0; j < vertices.size(); j++) {
                for (size_t vi = 0; vi < vertices[i]->adjacencies.size(); vi++) {
                    if (vertices[i]->adjacencies[vi].adjacency->id == vertices[j]->id) {
                        matrix[i][j] = vertices[i]->adjacencies[vi].weight;
                    }
                }
            }
        }
        return matrix;
    }

    // preenche e retorna uma matriz de zeros
    int** createMatrixOfZeros(size_t rows, size_t cols) {
        int** matrix = new int* [rows];
        for (size_t i = 0; i < rows; i++) {
            matrix[i] = new int[cols];
            for (size_t j = 0; j < cols; j++)
                matrix[i][j] = 0;
        }
        return matrix;
    }

    std::vector<Graph> getSubGraphs(){
        auto graphs = std::vector<Graph>();

        if(!isConnectivity()){
            for(size_t i = 0; i < vertices.size(); i++){
                // verifica se já pertence a um subgrafo
                bool isInSet = false;
                for(auto g : graphs){
                    for(auto v : g.vertices){
                        if(v->id == vertices[i]->id){
                            isInSet = true;
                            break;
                        }
                    }
                    if(isInSet) break;
                }
                if(isInSet) continue;

                // cria um novo subgrafo
                auto graph = Graph(std::to_string(i));
                // faz o fecho transitivo direto e indireto
                int* direct = directTransitiveClosure(vertices[i]);
                int* indirect = indirectTransitiveClosure(vertices[i]);

                // os vértices conexos são colocados no novo subgrafo
                for(size_t j = 0; j < vertices.size(); j++)
                    if(direct[j] != -1 && indirect[j] != -1)
                        graph.addVertex(getVertex(j));

                // o novo subgrafo é add à lista de subgrafos
                graphs.push_back(graph);
                size_t gsizes = 0;
                for(auto g : graphs) gsizes += g.vertices.size();
                // se não existirem mais vértices sobrando o algoritmo para
                if(gsizes == vertices.size()) break;
            }
        }

        return graphs;
    }

    std::string dijkstra(Vertex* vertex){
        std::string data = "";
        size_t size = vertices.size();
        auto dist = std::vector<size_t>(); // distância de cada nó partindo da fonte
        auto prev = std::vector<std::string>(); // distância de cada nó partindo da fonte
        auto isClosed = std::vector<bool>(); // vetor de fechados
        auto matrix = getAdjMatrix(); // matriz de adjacência do grafo

        // inicializa vetores
        for(size_t i = 0; i < size; i++){
            if(vertex->id == vertices[i]->id){
                dist.push_back(0);
            }else{
                dist.push_back(INFINITY);
            }
            prev.push_back("");
            isClosed.push_back(false);
        }

        // encontra o caminho de menor custo para todos os vértices
        for (size_t i = 0; i < size - 1; i++) {
            // pega a menor distância entre os vértices que ainda não foram fechados
            size_t min = INFINITY;
            size_t u;
            for (size_t v = 0; v < vertices.size(); v++){
                if (!isClosed[v] && dist[v] <= min){
                    min = dist[v];
                    u = v;
                }
            }
            // fecha o vértice
            isClosed[u] = true;

            for (size_t v = 0; v < size; v++){
                /*
                 *  dist[v] só é atualizado se:
                 *    ainda não foi fechado,
                 *    se tiver uma aresta entre u e v,
                 *    e o peso total do caminho partindo do vértice fonte para v
                 *    passando por u é menor que o valor atual de dist[v]
                 */
                if (!isClosed[v] && matrix[u][v] && dist[u] != INFINITY && dist[u] + matrix[u][v] < dist[v]){
                    // se todas as condições forem satisfeitas, a distância é atualizada
                    prev[v] = vertices[u]->id;
                    dist[v] = dist[u] + matrix[u][v];
                }
            }
        }

        // concatena o resultado
        data = "Vértice\t\tMenor dist.\tPrecedente\n";
        for (size_t i = 0; i < size; i++) {
            data += vertices[i]->id + "\t\t";
            if(dist[i] == INFINITY){
                data += "*\t\t";
            }else{
                data += std::to_string(dist[i]) + "\t\t";
            }
            data += prev[i] + "\n";
        }

        return data;
    }






    // ---------------- HERIKC ↓ ------------------------------------------------------------------//

    // Verifica se os vertice v1 � vizinho de v2, respeitando as dire��eos
    bool isNeighborhood(Vertex* v1, Vertex* v2) {
        for (size_t i = 0; i < v1->adjacencies.size(); i++)
            if (v1->adjacencies[i].adjacency->id == v2->id)
                return true;
        return false;
    }

    // Realiza a marca��o do vertice como visitado
    std::string visiting(bool*& visited, Vertex* vertex) {
        std::string dfsString = "";
        dfsString += "Vértice -> " + vertex->id + "\n";
        visited[indexOfVertex(vertex->id)] = true;

        return dfsString;
    }

    // Realiza a marca��oo do vertice como visitado e adiciona a lista
    std::string visiting(bool*& visited, std::list<Vertex*>& queue, Vertex* vertex) {
        std::string dfsString = "";
        dfsString += "Vértice -> " + vertex->id + "\n";
        visited[indexOfVertex(vertex->id)] = true;
        queue.push_back(vertex);

        return dfsString;
    }

    // Realiza a marca��o do vertice como visitado e adiciona a pilha
    std::string visiting(bool*& visited, std::stack<Vertex*>& stack, Vertex*& vertex, Vertex* oldvertex) {
        std::string dfsString = "";
        stack.push(oldvertex);
        vertex = stack.top();
        dfsString += "Vértice -> " + vertex->id + "\n";
        visited[indexOfVertex(vertex->id)] = true;

        return dfsString;
    }

    // DFS baseado na ordem de entrada
    std::string DFS(Vertex* vertex) {
        if(!existis(vertex->id)) return "";

        std::string cstr = "";

        std::stack<Vertex*> stack;
        size_t vector_size = vertices.size();
        bool* visited = new bool[vector_size];

        for (size_t i = 0; i < vector_size; i++)
            visited[i] = false;

        while (true) {
            // Verifica se o vertice atual j� foi visitado
            if (!visited[indexOfVertex(vertex->id)]) {
                cstr += "Vértice -> " + vertex->id + "\n";
                visited[indexOfVertex(vertex->id)] = true;
                stack.push(vertex);
            }

            Vertex* newI = getVertex(vertex->id);
            Vertex* newV = nullptr;
            bool find = false;

            for(size_t i = 0; i < vector_size; i++){
                for (size_t j = 0; j < newI->adjacencies.size(); j++) {
                    /*
                       Procura na lista de adjacencias do vertice atual o vertice correspodente
                       "i" = posi��o atual na lista de adjacencias
                       "j" = posi��o atual na lista de vertices
                    */
                    if(newI->adjacencies[j].adjacency->id._Equal(vertices[i]->id)) {
                        if (!visited[i]) {
                            newV = vertices[i];
                            find = true;
                            break;
                        }
                    }
                }
                if (find)
                    break;
            }

            if (find)
                vertex = newV; // Atualiza o vertex para o vertice adjacente
            else {
                // Remove da pilha e verifica se esta vazia
                stack.pop();

                if (stack.empty()) {
                    bool emptyVector = true;

                    // Devido a pilha estar vazia, ir� procurar um novo vertice que ainda n�o foi visitado
                    for (size_t j = 0; j < vector_size; j++) {
                        if (!visited[j]) {
                            stack.push(getVertex(j));
                            emptyVector = false;
                            break;
                        }
                    }

                    if(emptyVector)
                        break;
                }
                vertex = stack.top();
            }
        }

        return cstr;
    }

    // BFS baseadp na ordem de entrada
    std::string BFS(Vertex* vertex) {
        if(!existis(vertex->id)) return "";

        std::string cstr = "";

        std::list<Vertex*> queue;
        size_t vector_size = vertices.size();
        bool* visitados = new bool[vector_size];

        for (size_t i = 0; i < vector_size; i++)
            visitados[i] = false;

        // Marca o vertex inicial como visitado
        cstr += visiting(visitados, vertex);

        while (true) {
            Vertex* newI = getVertex(vertex->id);

            for (size_t i = 0; i < vector_size; i++) {
                for (size_t j = 0; j < newI->adjacencies.size(); j++) {
                    if (newI->adjacencies[j].adjacency->id._Equal(vertices[i]->id))
                    {
                        if (!visitados[i]) {
                            /*
                                Marca o vertice atual da lista de ajcacencia como visitado
                                Realizando atualiza��o de queue e vetor de visitados
                            */
                            cstr += visiting(visitados, queue, vertices[i]);
                        }
                    }

                }
            }

            // Verifica se a queue esta vazia, para atualizar a nova posi��o
            if (!queue.empty()) {
                vertex = queue.front();
                queue.pop_front();
            }
            else {
                bool emptyVector = true;

                // Devido a queue estar vazia, ir� procurar um novo vertice que ainda n�o foi visitado
                for (size_t j = 0; j < vector_size; j++) {
                    if (!visitados[j]) {
                        /*
                            Reinicia a queue para um novo vertice
                            Necess�rio marcar as flags e adicionar/removoer da queue
                        */
                        queue.push_back(getVertex(j));
                        emptyVector = false;

                        vertex = queue.front();
                        queue.pop_back();

                        cstr += visiting(visitados, vertex);
                        break;
                    }
                }

                if (emptyVector)
                    break;
            }
        }

        return cstr;
    }

    // Fecho transitivo Direto
    int* directTransitiveClosure(Vertex* vertex) {
        int** matrix = getAdjMatrix();

        size_t vector_size = vertices.size();
        int* waitList = new int[vector_size];
        bool* visit_ended = new bool[vector_size];

        for (size_t i = 0; i < vector_size; i++)
            waitList[i] = (-1);

        for (size_t i = 0; i < vector_size; i++)
            visit_ended[i] = false;

        size_t index = indexOfVertex(vertex->id);
        waitList[index] = 0;
        int distance = 1;

        while (true) {
            for (size_t j = 0; j < vector_size; j++) {
                if (matrix[index][j] == 1 && !visit_ended[j] && waitList[j] == (-1)) {
                    waitList[j] = distance;
                    //std::cout << "Vertice: " << getVertex(j)->id << " marcado com a distancia -> " << distance << std::endl;
                }
            }

            visit_ended[index] = true;
            index = -1;
            for (size_t i = 0; i < vector_size; i++) {
                if (waitList[i] != (-1) && !visit_ended[i] && waitList[i] == distance - 1) {
                    //std::cout << waitList[i] << std::endl << distance << std::endl << visit_ended[i] << std::endl << i << std::endl;
                    index = i;
                    distance = waitList[i] + 1;
                    break;
                }
            }

            if (index == (size_t)-1) {
                for (size_t i = 0; i < vector_size; i++) {
                    if (waitList[i] != (-1) && !visit_ended[i]) {
                        //std::cout << waitList[i] << std::endl << distance << std::endl << visit_ended[i] << std::endl << i << std::endl;
                        index = i;
                        distance = waitList[i] + 1;
                        break;
                    }
                }
            }

            if (index == (size_t)-1)
                break;

            bool existNull = false;
            for (size_t i = 0; i < vector_size; i++)
                if (waitList[i] == (-1))
                    existNull = true;

            if (!existNull)
                break;
        }

        std::cout << std::endl;
        for (size_t i = 0; i < vector_size; i++)
            std::cout << waitList[i] << " ";

        return waitList;
    }

    // Fecho transitivo Indireto
    int* indirectTransitiveClosure(Vertex* vertex) {
        int** matrix = getAdjMatrix();

        size_t vector_size = vertices.size();
        int* waitList = new int[vector_size];
        bool* visit_ended = new bool[vector_size];

        for (size_t i = 0; i < vector_size; i++)
            waitList[i] = (-1);

        for (size_t i = 0; i < vector_size; i++)
            visit_ended[i] = false;

        size_t index = indexOfVertex(vertex->id);
        waitList[index] = 0;
        int distance = 1;

        while (true) {
            for (size_t i = 0; i < vector_size; i++) {
                if (matrix[i][index] == 1 && !visit_ended[i] && waitList[i] == (-1)) {
                    waitList[i] = distance;
                    //std::cout << "Vertice: " << getVertex(i)->id << " marcado com a distancia -> " << distance << std::endl;
                }
            }

            visit_ended[index] = true;
            index = -1;
            for (size_t i = 0; i < vector_size; i++) {
                if (waitList[i] != (-1) && !visit_ended[i] && waitList[i] == distance - 1) {
                    //std::cout << waitList[i] << std::endl << distance << std::endl << visit_ended[i] << std::endl << i << std::endl;
                    index = i;
                    distance = waitList[i] + 1;
                    break;
                }
            }

            if (index == (size_t)-1) {
                for (size_t i = 0; i < vector_size; i++) {
                    if (waitList[i] != (-1) && !visit_ended[i]) {
                        //std::cout << waitList[i] << std::endl << distance << std::endl << visit_ended[i] << std::endl << i << std::endl;
                        index = i;
                        distance = waitList[i] + 1;
                        break;
                    }
                }
            }

            if (index == (size_t)-1)
                break;

            bool existNull = false;
            for (size_t i = 0; i < vector_size; i++)
                if (waitList[i] == (-1))
                    existNull = true;

            if (!existNull)
                break;
        }

        std::cout << std::endl;
        for (size_t i = 0; i < vector_size; i++)
            std::cout << waitList[i] << " ";

        return waitList;
    }

    // Verifica se o grafo é Conexo
    bool isConnectivity() {
        int* direct = directTransitiveClosure(vertices[0]);
        int* indirect = indirectTransitiveClosure(vertices[0]);

        for (size_t i = 0; i < vertices.size(); i++) {
            if (direct[i] != indirect[i])
                return false;
        }
        return true;
    }
  
    // Retorna Grafo com a Estrutura de Caminho Critico
    static Graph criticalPathGraph(std::vector<std::string> activity, std::vector<int> duration, std::vector<std::string> previous) {
        size_t vector_size = activity.size();
        bool* visited = new bool[vector_size];
        std::vector<std::vector<std::string>> previousPro;
        auto vertex = std::vector<Vertex*>();

        // Cria vetor de visitados para os vertices
        // Cria uma nova lista de previous, visto que Previous, é uma string com mais de um elemento separado por ","
        // Cria o vetor de vertex do grafo adicionando a duração
        for (size_t i = 0; i < vector_size; i++) {
            visited[i] = false;
            previousPro.push_back(split(previous[i], ','));
            vertex.push_back(new CriticVertex(activity[i], duration[i]));
        }

        std::string vertexEnd = "FIM";
        // Adiciona o Vertice de FIM
        vertex.push_back(new CriticVertex(vertexEnd));

        // Adiciona o vetor ao Grafo com nome Critical
        Graph* critical = new Graph("Critical", vertex);

        // Adiciona as conexões de acordo com o vetor de previousPro
        for(size_t i = 0; i < previousPro.size(); i++) {
            for(size_t j = 0; j < previousPro[i].size(); j++){
                if(!previousPro[i][j]._Equal("")) {
                    critical->addEdge(previousPro[i][j], activity[i], 0);
                }
            }
        }

        bool allVertexVisited = false;
        int maxEnd = -1;
        // Caminho de ida do caminho critico, faça enquanto todos os vertices não forem visitados
        do{
            for(size_t i = 0; i < vector_size; i++){
                if(!visited[i]){ // Verifica se o vertice já foi visitado, para não realizar novamente
                    bool allPreviousVisited = true;

                    // Verifica se os seus precedentes já foram visitados, para não vistar na ordem errada
                    for(size_t j = 0; j < previousPro[i].size(); j++){
                        int index = critical->indexOfVertex(previousPro[i][j]);

                        if(previousPro[i][0]._Equal(""))
                            break;

                        if(index != (-1)) {
                            if(!visited[index]){
                                allPreviousVisited = false;
                                break;
                            }
                        }
                    }

                    // Se todos precedentes foram visitados, executa
                    if(allPreviousVisited){
                        visited[i] = true;
                        auto curVertex = (CriticVertex*)critical->vertices[i];

                        // Caso seja o vertice inicial, não terá precedente
                        if(previousPro[i].size() <= 0 || previousPro[i][0]._Equal("")) {
                            curVertex->minGoing = 1;
                            curVertex->maxGoing = duration[i];
                        }else { // Para os demais vertices preenche o min e max de ida
                            int maxGoing = -1;

                            // Verifica qual o precedente de maior duração, para associar ao novo vertice
                            for(size_t j = 0; j < previousPro[i].size(); j++){
                                int index = critical->indexOfVertex(previousPro[i][j]);
                                auto curForVertex = (CriticVertex*)critical->vertices[index];
                                if(curForVertex->maxGoing > maxGoing){
                                    maxGoing = curForVertex->maxGoing;
                                }
                            }
                            curVertex->minGoing = maxGoing + 1;
                            curVertex->maxGoing = maxGoing + duration[i];
                        }

                        if(curVertex->maxGoing > maxEnd){
                            maxEnd = curVertex->maxGoing;
                        }
                    }
                }
            }

            // Verifica se todos vertices foram visitados no caminho de ida
            allVertexVisited = true;
            for(size_t i = 0; i < vector_size; i++){
                if(!visited[i]){
                    allVertexVisited = false;
                    break;
                }
            }
        }while(!allVertexVisited);


        // Marca o tempo de minimo de ida e volta do vertice FIM
        size_t index = critical->indexOfVertex(vertexEnd);
        auto endVertex = (CriticVertex*)critical->vertices[index];
        endVertex->minGoing = maxEnd + 1;
        endVertex->minBack = maxEnd + 1;


        // Atualiza os vertices para não visitados novamente, para realizar o caminho de volta
        for (size_t i = 0; i < vector_size; i++) {
            visited[i] = false;
        }

        // Caminho de volta do caminho critico, faça enquanto todos os vertices não forem visitados
        do{
            for(size_t i = 0; i < vector_size; i++) {
                // Verifica se o vertice já foi visitado, para não realizar novamente
                if(!visited[i])
                {
                    // Primeiramente deve ser visitado somente os Vertices de Fim
                    if(critical->vertices[i]->adjacencies.size() <= 0)
                    {
                        visited[i] = true;
                        size_t index = critical->indexOfVertex(critical->vertices[i]->id);
                        auto curVertex = (CriticVertex*)critical->vertices[index];
                        curVertex->maxBack = maxEnd;
                        curVertex->minBack = maxEnd - duration[index] + 1;
                        curVertex->dayOff = curVertex->maxBack - curVertex->maxGoing;
                    }
                    else
                    {
                        bool adjacencyesVisited = true;
                        int maxBack = 999999;

                        for(size_t j = 0; j < critical->vertices[i]->adjacencies.size(); j++){
                            size_t adjacencyIndex = critical->indexOfVertex(critical->vertices[i]->adjacencies[j].adjacency->id);
                            auto curAdjacencyVertex = (CriticVertex*)critical->vertices[adjacencyIndex];

                            if(!visited[adjacencyIndex])
                            {
                                adjacencyesVisited = false;
                                break;
                            }
                            else if(curAdjacencyVertex->minBack < maxBack)
                            {
                                maxBack = curAdjacencyVertex->minBack;
                            }
                        }

                        if(adjacencyesVisited)
                        {
                            visited[i] = true;
                            size_t index = critical->indexOfVertex(critical->vertices[i]->id);
                            auto curVertex = (CriticVertex*)critical->vertices[index];
                            curVertex->maxBack = maxBack - 1;
                            curVertex->minBack = curVertex->maxBack - duration[index] + 1;
                            curVertex->dayOff = curVertex->maxBack - curVertex->maxGoing;
                        }
                    }
                }
            }       

            allVertexVisited = true;
            for(size_t i = 0; i < vector_size; i++) {
                if(!visited[i])
                {
                    allVertexVisited = false;
                    break;
                }
            }
        }while(!allVertexVisited);


        // Liga os vertices sem adjacentes ao vertice de FIM
        for(size_t i = 0; i < vector_size; i++){
            if(critical->vertices[i]->adjacencies.size() <= 0){
                critical->addEdge(activity[i], vertexEnd, 0);
            }
        }


        return *critical;
    }

    // Retorna Caminho Critico do Grafo
    static std::vector<std::string> criticalPath(Graph* graph) {
        auto critical = std::vector<std::string>();
        critical.push_back("Início");

        size_t vector_size = graph.vertices.size();

        auto curVertex = (CriticVertex*)graph.vertices[0];
        for(size_t i = 0; i < vector_size; i++){

            if(curVertex->dayOff == 0) {
                critical.push_back(curVertex->id);

                bool findedNewZeroDayOff = false;
                for(size_t j = 0; j < curVertex->adjacencies.size(); j++) {
                    auto adjacencyVertex = (CriticVertex*)curVertex->adjacencies[j].adjacency;

                    if(adjacencyVertex->dayOff == 0){
                        curVertex = adjacencyVertex;
                        findedNewZeroDayOff = true;
                        break;
                    }
                }

                if(!findedNewZeroDayOff){
                    break;
                }
            }
            if(curVertex->dayOff == (-1) || curVertex->dayOff != 0)
                break;
        }

        critical.push_back("Fim");

        return critical;
    }

};

#endif // GRAPH_H
