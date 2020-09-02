#include <iostream>
#include "test.h"
#include "Graph.h"
#include "cmd.h"
#include "util.h"

std::vector<Graph> graphs;

int main(void) {
	graphs = readGraphData();


	//loadPrintTest(graphs);
	//testGraph();

	return EXIT_SUCCESS;
}
