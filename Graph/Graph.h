#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stack>

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

	// Adiciona um novo vértice
	bool addVertex(Vertex* vertex) {
		if (not existis(vertex->id)) {
			vertices.push_back(vertex);
			return true;
		}
		return false;
	}

	// Remove um vértice à partir do id
	bool removeVertex(std::string id) {
		for (auto i = 0; i < vertices.size(); i++) {
			if (vertices[i]->id._Equal(id)) {
				vertices.erase(vertices.begin() + i);
				return true;
			}
		}
		return false;
	}

	// Verifica se um vértice existe
	bool existis(std::string id) {
		for (auto v : vertices)
			if (v->id._Equal(id)) return true;
		return false;
	}

	// Adiciona uma nova aresta à partir do id do vértice 1 e do vértice 2
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

	// Remove uma aresta à partir do id do vértice 1 e do vértice 2
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

	int getDegreeOutput(std::string id) { return 0; }
	int getDegreeInput(std::string id) { return 0; }

	bool isNeighborhood(std::string id1, std::string id2) { 
		
		return true;
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

	void DFS(Vertex* vertex) {
		std::stack<Vertex*> pilha;
		int vector_size = vertices.size();
		bool* visitados = new bool[vector_size];

		for (int i = 0; i < vector_size; i++) 
			visitados[i] = false;

		while (true) {
			// Verifica se o vertice atual já foi visitado
			if (!visitados[indexOfVertex(vertex->id)]) {
				std::cout << "Visitando vertice " << vertex->id << std::endl;
				visitados[indexOfVertex(vertex->id)] = true;
				pilha.push(vertex);
			}

			bool find = false;
			Vertex* newV = nullptr;

			for(auto i = 0; i < getVertex(vertex->id)->adjacencies.size(); i++){
				for (auto j = 0; j < vector_size; j++) {

					/* 
					   Procura na lista de adjacencias do vertice atual o vertice correspodente
					   "i" = posição atual na lista de adjacencias 
					   "j" = posição atual na lista de vertices 
					*/
					if(getVertex(vertex->id)->adjacencies[i]->id._Equal(vertices[j]->id))
					{
						if (!visitados[j]) {
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
				pilha.pop();		

				if (pilha.empty()) {
					bool emptyVector = true;

					// Devido a pilha estar vazia, irá procurar um novo vertice que ainda não foi visitado
					for (auto j = 0; j < vector_size; j++) {
						if (!visitados[j]) {
							pilha.push(getVertex(j));
							emptyVector = false;
							break;
						}
					}

					if(emptyVector)
						break;
				}
				vertex = pilha.top();
			}
		}
	}
};
