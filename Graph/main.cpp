#include <iostream>
#include "packages/BPS/BPS.h"
#include "Graph.h"

int main(void) {
	Graph graph = Graph("test");

	graph.addVertex(new Vertex("1"));
	graph.addVertex(new Vertex("2"));
	graph.addVertex(new Vertex("3"));
	graph.addVertex(new Vertex("4"));

	graph.addEdge("1", "2");
	graph.addEdge("1", "3");
	graph.addEdge("1", "4");
	graph.addEdge("2", "3");
	graph.addEdge("2", "4");
	graph.addEdge("3", "4");

	return EXIT_SUCCESS;
}
