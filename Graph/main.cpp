#include <iostream>
#include "test.h"
#include "graph.h"
#include "cmd.h"
#include "util.h"
#include "plot.h"

std::vector<Graph> graphs;

int main(void) {
	bool running = true;

	graphs = readGraphData();

	while (running) {
		auto line = readConsole();
		std::vector<std::string> tokens;
	}

	//loadPrintTest(graphs);
	//plotGraph(graphs[5]);
	//loadPrintTest(graphs);
	//graphs[4].BFS(graphs[4].getVertex("a"));
	//testGraph();

	return EXIT_SUCCESS;
}
