#include <iostream>
#include "Graph.h"
#include "parser.h"
#include "util.h"

void loadPrintTest(std::vector<Graph> graphs) {
	for (auto graph : graphs) {
		printAdjacencyVector(graph.getVector(), graph.text);
		printAdjacencyMatrix(graph.getMatrix(), graph.vertices.size(), graph.vertices, graph.text);
	}
}

void addRemoveTest() {
	Graph graph = Graph("test");

	graph.addVertex(new Vertex("1"));
	graph.addVertex(new Vertex("2"));
	graph.addVertex(new Vertex("3"));
	graph.addVertex(new Vertex("4"));

	graph.addEdge("1", "2");
	graph.addEdge("1", "3");
	graph.addEdge("2", "3");
	graph.addEdge("2", "4");
	graph.addEdge("3", "4");

	printAdjacencyVector(graph.getVector(), graph.text);
	printAdjacencyMatrix(graph.getMatrix(), graph.vertices.size(), graph.vertices, graph.text);

	// Vertex ---------------------------------------------------
	//graph.removeVertex("1");

	//printAdjacencyVector(graph.getVector(), graph.text);
	//printAdjacencyMatrix(graph.getMatrix(), graph.vertices.size(), graph.text);

	//graph.removeVertex("4");

	//printAdjacencyVector(graph.getVector(), graph.text);
	//printAdjacencyMatrix(graph.getMatrix(), graph.vertices.size(), graph.text);

	//graph.addVertex(new Vertex("5"));

	//printAdjacencyVector(graph.getVector(), graph.text);
	//printAdjacencyMatrix(graph.getMatrix(), graph.vertices.size(), graph.text);


	// Edge ---------------------------------------------------
	//graph.removeEdge("1", "2");

	//printAdjacencyVector(graph.getVector(), graph.text);
	//printAdjacencyMatrix(graph.getMatrix(), graph.vertices.size(), graph.text);

	//graph.removeEdge("2", "4");

	//printAdjacencyVector(graph.getVector(), graph.text);
	//printAdjacencyMatrix(graph.getMatrix(), graph.vertices.size(), graph.text);

	//graph.addEdge("1", "2");

	//printAdjacencyVector(graph.getVector(), graph.text);
	//printAdjacencyMatrix(graph.getMatrix(), graph.vertices.size(), graph.text);
}

