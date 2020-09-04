#include <iostream>
#include "test.h"
#include "Graph.h"
#include "cmd.h"
#include "util.h"

std::vector<Graph> graphs;

int main(void) {
	graphs = readGraphData();

	loadPrintTest(graphs);
	graphs[4].BFS(graphs[4].getVertex("a"));

	//testGraph();

	return EXIT_SUCCESS;
}
