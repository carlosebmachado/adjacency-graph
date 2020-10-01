#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <list> 
#include <queue> // fila para usar na BFS

// Preenche e retorna uma matriz de zeros
int** createMatrixZeros(size_t rows, size_t cols) {
	int** matrix = new int* [rows];
	for (auto i = 0; i < rows; i++) {
		matrix[i] = new int[cols];
		for (auto j = 0; j < cols; j++)
			matrix[i][j] = 0;
	}
	return matrix;
}

class Vertex {
public:
	std::string id;
	int x, y;
	std::vector<Vertex*> adjacencies;

	Vertex(std::string id) {
		this->x = 0;
		this->y = 0;
		this->id = id;
		adjacencies = std::vector<Vertex*>();
	}

	Vertex(int x, int y, std::string id) {
		this->x = x;
		this->y = y;
		this->id = id;
		adjacencies = std::vector<Vertex*>();
	}

	Vertex(std::string id, std::vector<Vertex*> adjacencies) {
		this->x = 0;
		this->y = 0;
		this->id = id;
		this->adjacencies = adjacencies;
	}

	Vertex(int x, int y, std::string id, std::vector<Vertex*> adjacencies) {
		this->x = x;
		this->y = y;
		this->id = id;
		this->adjacencies = adjacencies;
	}
};

class Graph {
public:
	std::string text;
	std::vector<Vertex*> vertices;

	Graph(std::string text) {
		this->text = text;
		vertices = std::vector<Vertex*>();
	}

	Graph(std::string text, std::vector<Vertex*> vertices) {
		this->text = text;
		this->vertices = vertices;
	}

	// Adiciona um novo v�rtice
	bool addVertex(Vertex* vertex) {
		if (not existis(vertex->id)) {
			vertices.push_back(vertex);
			return true;
		}
		return false;
	}

	// Remove um v�rtice � partir do id
	bool removeVertex(std::string id) {
		for (auto i = 0; i < vertices.size(); i++) {
			if (vertices[i]->id._Equal(id)) {
				vertices.erase(vertices.begin() + i);
				return true;
			}
		}
		return false;
	}

	// Verifica se um v�rtice existe
	bool existis(std::string id) {
		for (auto v : vertices)
			if (v->id._Equal(id)) return true;
		return false;
	}

	// Adiciona uma nova aresta � partir do id do v�rtice 1 e do v�rtice 2
	bool addEdge(std::string id1, std::string id2) {
		for (auto v1 : vertices) {
			if (v1->id._Equal(id1)) {
				for (auto v2 : vertices) {
					if (v2->id._Equal(id2)) {
						v1->adjacencies.push_back(v2);
						return true;
					}
				}
			}
		}
		return false;
	}

	// Remove uma aresta � partir do id do v�rtice 1 e do v�rtice 2
	bool removeEdge(std::string id1, std::string id2) {
		for (auto v1 : vertices) {
			if (v1->id._Equal(id1)) {
				for (auto v2 = 0; v2 < v1->adjacencies.size(); v2++) {
					if (v1->adjacencies[v2]->id._Equal(id2)) {
						v1->adjacencies.erase(v1->adjacencies.begin() + v2);
						return true;
					}
				}
			}
		}
		return false;
	}

	// 
	Vertex* getVertex(std::string id) {
		for (auto i = 0; i < vertices.size(); i++) {
			if (vertices[i]->id._Equal(id)) {
				return vertices[i];
			}
		}
		return nullptr;
	}

	Vertex* getVertex(int index) {
		return vertices[index];
	}

	// 
	int indexOfVertex(std::string id) {
		for (auto i = 0; i < vertices.size(); i++) {
			if (vertices[i]->id._Equal(id)) {
				return i;
			}
		}
		return -1;
	}

	std::vector<std::vector<std::string>> getVector() {
		auto adjVector = std::vector<std::vector<std::string>>();
		for (auto v : vertices) {
			adjVector.push_back(std::vector<std::string>());
			adjVector[adjVector.size() - 1].push_back("([ " + v->id + " ])");
			for (auto a : v->adjacencies) {
				adjVector[adjVector.size() - 1].push_back(" -> [ " + a->id + " ]");
			}
		}
		return adjVector;
	}

	int** getMatrix() {
		auto matrix = createMatrixZeros(vertices.size(), vertices.size());
		for (auto i = 0; i < vertices.size(); i++) {
			for (auto j = 0; j < vertices.size(); j++) {
				for (auto vi = 0; vi < vertices[i]->adjacencies.size(); vi++) {
					if (vertices[i]->adjacencies[vi]->id._Equal(vertices[j]->id)) {
						matrix[i][j] = 1;
					}
				}
			}
		}
		return matrix;
	}

	// Verifica se os vertice v1 � vizinho de v2, respeitando as dire��eos
	bool isNeighborhood(Vertex* v1, Vertex* v2) {
		for (int i = 0; i < v1->adjacencies.size(); i++)
			if (v1->adjacencies[i]->id == v2->id)
				return true;
		return false;
	}

	// Realiza a marca��o do vertice como visitado
	void visiting(bool*& visited, Vertex* vertex) {
		std::cout << "Visitando vertice " << vertex->id << std::endl;
		visited[indexOfVertex(vertex->id)] = true;
	}

	// Realiza a marca��oo do vertice como visitado e adiciona a lista
	void visiting(bool*& visited, std::list<Vertex*>& queue, Vertex* vertex) {
		std::cout << "Visitando vertice " << vertex->id << std::endl;
		visited[indexOfVertex(vertex->id)] = true;
		queue.push_back(vertex);
	}

	// Realiza a marca��o do vertice como visitado e adiciona a pilha
	void visiting(bool*& visited, std::stack<Vertex*>& stack, Vertex*& vertex, Vertex* oldvertex) {
		stack.push(oldvertex);
		vertex = stack.top();
		std::cout << "Visitando vertice " << vertex->id << std::endl;
		visited[indexOfVertex(vertex->id)] = true;
	}

	// DFS baseado na ordem de entrada 
	void DFS(Vertex* vertex) {
		std::stack<Vertex*> stack;
		int vector_size = vertices.size();
		bool* visited = new bool[vector_size];

		for (int i = 0; i < vector_size; i++) 
			visited[i] = false;

		while (true) {
			// Verifica se o vertice atual j� foi visitado
			if (!visited[indexOfVertex(vertex->id)]) {
				std::cout << "Visitando vertice " << vertex->id << std::endl;
				visited[indexOfVertex(vertex->id)] = true;
				stack.push(vertex);
			}
			
			Vertex* newI = getVertex(vertex->id);
			Vertex* newV = nullptr;
			bool find = false;

			for(auto i = 0; i < newI->adjacencies.size(); i++){
				for (auto j = 0; j < vector_size; j++) {
					/* 
					   Procura na lista de adjacencias do vertice atual o vertice correspodente
					   "i" = posi��o atual na lista de adjacencias 
					   "j" = posi��o atual na lista de vertices 
					*/
					if(newI->adjacencies[i]->id._Equal(vertices[j]->id)) {
						if (!visited[j]) {
							newV = vertices[j];
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
					for (auto j = 0; j < vector_size; j++) {
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
	}

	// DFS baseada na Matrix
	void DFSMatrix(Vertex* vertex) {
		int** matrix = getMatrix();
		std::stack<Vertex*> stack;
		int vector_size = vertices.size();
		bool* visited = new bool[vector_size];

		for (int i = 0; i < vector_size; i++)
			visited[i] = false;

		// Realiza a marca��o do primeiro vertice como visitado
		visiting(visited, stack, vertex, vertex);

		while (true) {
			bool find = false;

			for (auto i = 0; i < vector_size; i++) {
				if (indexOfVertex(vertex->id) == i) { // Compara indice do vertice com a linha da matrix
					for (auto j = 0; j < vector_size; j++) {
						if (matrix[i][j] == 1 && !visited[j]) {
							// Visita o vertice e adiciona a pilha
							visiting(visited, stack, vertex, vertices[j]);
							break;
						}
					}
				}
				if (find)
					break;
			}

			if (!find) {
				stack.pop();

				if (stack.empty()) {
					bool emptyVector = true;

					// Devido a pilha estar vazia, ir� procurar um novo vertice que ainda n�o foi visitado
					for (auto j = 0; j < vector_size; j++) {
						if (!visited[j]) {
							visiting(visited, stack, vertex, getVertex(j));	
							emptyVector = false;
							break;
						}
					}

					if (emptyVector)
						break;
				}
				else 
					vertex = stack.top();
			
			}
		}	
	}

	// BFS baseadp na ordem de entrada
	void BFS(Vertex* vertex) {
		std::list<Vertex*> queue;
		int vector_size = vertices.size();
		bool* visitados = new bool[vector_size];

		for (int i = 0; i < vector_size; i++)
			visitados[i] = false;

		// Marca o vertex inicial como visitado
		visiting(visitados, vertex);

		while (true) {
			Vertex* newV = nullptr;
			Vertex* newI = getVertex(vertex->id);

			for (auto i = 0; i < newI->adjacencies.size(); i++) {
				for (auto j = 0; j < vector_size; j++) {

					if (newI->adjacencies[i]->id._Equal(vertices[j]->id))
					{
						if (!visitados[j]) {
							/*
								Marca o vertice atual da lista de ajcacencia como visitado
								Realizando atualiza��o de queue e vetor de visitados
							*/
							visiting(visitados, queue, vertices[j]);							
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
				for (auto j = 0; j < vector_size; j++) {
					if (!visitados[j]) {
						/*
							Reinicia a queue para um novo vertice
							Necess�rio marcar as flags e adicionar/removoer da queue
						*/
						queue.push_back(getVertex(j));
						emptyVector = false;

						vertex = queue.front();
						queue.pop_back();

						visiting(visitados, vertex);
						break;
					}
				}

				if (emptyVector)
					break;
			}				
		}
	}

	// Fecho transitivo Direto
	int* directTransitiveClosure(Vertex* vertex) {
		int** matrix = getMatrix();

		int vector_size = vertices.size();
		int* waitList = new int[vector_size];
		bool* visit_ended = new bool[vector_size];

		// Cria vetor denominando todos vertices como não encontrados
		for (int i = 0; i < vector_size; i++)
			waitList[i] = (-1);

		for (int i = 0; i < vector_size; i++)
			visit_ended[i] = false;

		int index = indexOfVertex(vertex->id);
		waitList[index] = 0;
		int distance = 1;

		while (true) {
			// Percore para o proximo vertice adjacente e marca a distancia
			for (int j = 0; j < vector_size; j++) {
				if (matrix[index][j] == 1 && !visit_ended[j] && waitList[j] == (-1)) {
					waitList[j] = distance;
				}
			}		

			visit_ended[index] = true;
			index = -1;

			// Procura o novo indice de acordo com a distancia
			for (int i = 0; i < vector_size; i++) {
				if (waitList[i] != (-1) && !visit_ended[i] && waitList[i] == distance - 1) {
					index = i;
					distance = waitList[i] + 1;
					break;
				}
			}

			// Caso não seja encontrado anteriormente, procura nos outros grafos de mesma distancia
			if (index == -1) {
				for (int i = 0; i < vector_size; i++) {
					if (waitList[i] != (-1) && !visit_ended[i]) {
						index = i;
						distance = waitList[i] + 1;
						break;
					}
				}
			}

			// Caso não seja encontrado novamente, finaliza a busca
			if (index == -1)
				break;

			bool existNull = false;
			for (int i = 0; i < vector_size; i++)
				if (waitList[i] == (-1))
					existNull = true;

			if (!existNull)
				break;
		}

		return waitList;
	}

	// Fecho transitivo Indireto
	int* indirectTransitiveClosure(Vertex* vertex) {
		int** matrix = getMatrix();

		int vector_size = vertices.size();
		int* waitList = new int[vector_size];
		bool* visit_ended = new bool[vector_size];

		// Cria vetor denominando todos vertices como não encontrados
		for (int i = 0; i < vector_size; i++)
			waitList[i] = (-1);

		for (int i = 0; i < vector_size; i++)
			visit_ended[i] = false;

		int index = indexOfVertex(vertex->id);
		waitList[index] = 0;
		int distance = 1;

		while (true) {
			// Percore para o proximo vertice adjacente e marca a distancia
			for (int i = 0; i < vector_size; i++) {
				if (matrix[i][index] == 1 && !visit_ended[i] && waitList[i] == (-1)) {
					waitList[i] = distance;
				}
			}

			visit_ended[index] = true;
			index = -1;

			// Procura o novo indice de acordo com a distancia			
			for (int i = 0; i < vector_size; i++) {
				if (waitList[i] != (-1) && !visit_ended[i] && waitList[i] == distance - 1) {
					index = i;
					distance = waitList[i] + 1;
					break;
				}
			}

			// Caso não seja encontrado anteriormente, procura nos outros grafos de mesma distancia
			if (index == -1) {
				for (int i = 0; i < vector_size; i++) {
					if (waitList[i] != (-1) && !visit_ended[i]) {
						index = i;
						distance = waitList[i] + 1;
						break;
					}
				}
			}

			// Caso não seja encontrado novamente, finaliza a busca
			if (index == -1)
				break;

			bool existNull = false;
			for (int i = 0; i < vector_size; i++)
				if (waitList[i] == (-1))
					existNull = true;

			if (!existNull)
				break;
		}

		return waitList;
	}
	
	// Verifica se o grafo � Conexo
	bool isConnectivity() {
		int* direct = directTransitiveClosure(vertices[0]);
		int* indirect = indirectTransitiveClosure(vertices[0]);

		int counterDirect = 0;
		int counterIndirect = 0;
		for (int i = 0; i < vertices.size(); i++) {
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
