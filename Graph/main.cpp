#include <iostream>
#include "test.h"
#include "Graph.h"
#include "cmd.h"
#include "util.h"

std::vector<Graph> graphs;

int main(void) {
	graphs = readGraphData();

	loadPrintTest(graphs);
	int NGrafo = 6;
	graphs[NGrafo].DFS(graphs[NGrafo].getVertex("a"));

	//testGraph();

	return EXIT_SUCCESS;
}
