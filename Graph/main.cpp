#include <iostream>
#include "test.h"
#include "graph.h"
#include "cmd.h"
#include "util.h"
#include "plot.h"

std::vector<Graph> graphs;

int main(void) {
	graphs = readGraphData();

	loadPrintTest(graphs);
	plotGraph(graphs[5]);


	//loadPrintTest(graphs);
	//graphs[4].BFS(graphs[4].getVertex("a"));

	//testGraph();

	return EXIT_SUCCESS;
}
