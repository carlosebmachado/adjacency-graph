#include <iostream>
#include "test.h"
#include "Graph.h"
#include "cmd.h"
#include "util.h"

std::vector<Graph> graphs;

int main(void) {
	graphs = readGraphData();

	loadPrintTest(graphs);
	graphs[2].DFS(graphs[2].getVertex("a"));
	//testGraph();

	return EXIT_SUCCESS;
}
