#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "BPS.h"
#include "Graph.h"

std::vector<Graph> readGraphData() {
    auto graphs = std::vector<Graph>();
    BPS::File* file = BPS::read("graph_data.bps");

    for (auto section : file->findAll()) {
        Graph graph = Graph(section->find("name")->getValue());
        auto lstrv = BPS::split(section->find("vertices")->getValue(), ',');
        auto lstre = BPS::split(section->find("edges")->getValue(), '|');
        
        for (auto v : lstrv) {
            graph.addVertex(new Vertex(v));
        }
        for (auto e : lstre) {
            auto p1p2 = BPS::split(e, ',');
            graph.addEdge(p1p2[0], p1p2[1]);
        }
        graphs.push_back(graph);
    }
    return graphs;
}

void printAdjacencyVector(std::vector<std::vector<std::string>> adjVertex, std::string text) {
    std::cout << std::endl << std::endl << "----------------------------------" << std::endl;
    std::cout << "Adjacency Vector: " << text << std::endl << std::endl;
    for (auto v : adjVertex) {
        for (auto t : v) {
            std::cout << t;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << "----------------------------------" << std::endl << std::endl;
}

void printAdjacencyMatrix(int** adjMatrix, size_t size, std::vector<Vertex*> vertices, std::string text) {
    std::cout << std::endl << std::endl << "----------------------------------" << std::endl;
    std::cout << "Adjacency Matrix: " << text << std::endl << std::endl;
    for (auto i = 0; i < size; i++) std::cout << "     " << vertices[i]->id;
    std::cout << std::endl;
    for (auto i = 0; i < size; i++) {
        std::cout << vertices[i]->id << " ";
        for (auto j = 0; j < size; j++) {
            std::cout << " [ "<<adjMatrix[i][j] << " ]";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << "----------------------------------" << std::endl << std::endl;
}
