#include <iostream>
#include "test.h"
#include "graph.h"
#include "cmd.h"
#include "util.h"
#include "plot.h"

#define DEBUG false

enum Level {
	e_MAIN,
	e_SECOND
};

std::vector<Graph> graphs;
Graph* curGraph = nullptr;

void addGraph(std::vector<std::string>);
void remGraph(std::vector<std::string>);
void selGraph();
void addVertex();
void addEdge();
void remVertex();
void remEdge();
void graphBFS();
void graphDFS();
void graphPlot();
void back();
void error();
void noCommand();
void printError(std::string);

int main(void) {
	bool running = true;

	graphs = readGraphData();

	if (DEBUG) running = false;

	while (running) {
		auto line = readConsole();
		auto tokens = scanner(line);
		auto command = parser(tokens);

		switch (command) {
		case e_ADD_GRAPH:
			addGraph(tokens);
			break;
		case e_REM_GRAPH:
			remGraph(tokens);
			break;
		case e_SEL_GRAPH:
			selGraph();
			break;
		case e_ADD_VERTEX:
			addVertex();
			break;
		case e_ADD_EDGE:
			addEdge();
			break;
		case e_REM_VERTEX:
			remVertex();
			break;
		case e_REM_EDGE:
			remEdge();
			break;
		case e_BFS:
			graphBFS();
			break;
		case e_DFS:
			graphDFS();
			break;
		case e_PLOT:
			graphPlot();
			break;
		case e_BACK:
			back();
			break;
		case e_EXIT:
			running = false;
			break;
		case e_ERROR:
			error();
			break;
		case e_NOCOMMAND:
			noCommand();
			break;
		}
	}

	if (DEBUG) mainTest();

	return EXIT_SUCCESS;
}

void addGraph(std::vector<std::string> param) {
	
}

void remGraph(std::vector<std::string> param) {

}

void selGraph() {

}

void addVertex() {

}

void addEdge() {

}

void remVertex() {

}

void remEdge() {

}

void graphBFS() {

}

void graphDFS() {

}

void graphPlot() {

}

void back() {

}

void error() {

}

void noCommand() {

}

void printError(std::string msg) {
	std::cout << msg << std::endl;
}
