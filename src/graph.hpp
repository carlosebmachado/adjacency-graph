#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <list>
#include <queue>

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
        auto isClosed = std::vector<bool>(); // vetor de fechados
        auto matrix = getAdjMatrix(); // matriz de adjacência do grafo

        // inicializa vetores
        for(size_t i = 0; i < size; i++){
            if(vertex->id == vertices[i]->id){
                dist.push_back(0);
            }else{
                dist.push_back(INFINITY);
            }
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
                /*  dist[v] só é atualizado se:
                 *    ainda não foi fechado,
                 *    se tiver uma aresta entre u e v,
                 *    e o peso total do caminho partindo do vértice fonte para v
                 *    passando por u é menor que o valor atual de dist[v]
                 */
                if (!isClosed[v] && matrix[u][v] && dist[u] != INFINITY && dist[u] + matrix[u][v] < dist[v]){
                    // se todas as condições forem satisfeitas, a distância é atializada
                    dist[v] = dist[u] + matrix[u][v];
                }
            }
        }

        // concatena o resultado
        data = "Vértice        Menor dist.                     '\n";
        for (size_t i = 0; i < size; i++) {
            data += vertices[i]->id + "                  ";
            if(dist[i] == INFINITY){
                data += "*                      ";
            }else{
                data += std::to_string(dist[i]) + "\n";
            }
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

                    std::string tempIdNewI = newI->adjacencies[j].adjacency->id;
                    std::string tempIdVerticeI = vertices[i]->id;

                    if (newI->adjacencies[j].adjacency->id._Equal(vertices[i]->id))
                    {
                        if (!visitados[i]) {
                            /*
                                Marca o vertice atual da lista de ajcacencia como visitado
                                Realizando atualiza��o de queue e vetor de visitados
                            */
                            tempIdNewI = newI->adjacencies[j].adjacency->id;
                            tempIdVerticeI = vertices[i]->id;
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

        int counterDirect = 0;
        int counterIndirect = 0;
        for (size_t i = 0; i < vertices.size(); i++) {
            if (direct[i] == (-1))
                counterDirect++;
            if (indirect[i] == (-1))
                counterIndirect++;
        }

        if (counterDirect != counterIndirect)
            return false;
        else
            return true;

    }

};

#endif // GRAPH_H
