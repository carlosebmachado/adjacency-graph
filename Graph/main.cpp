#include <iostream>
#include "test.h"
#include "graph.h"
#include "parser.h"
#include "util.h"
#include "plot.h"

#define DEBUG false

std::vector<Graph> graphs;
Graph* curGraph;

void addGraph(std::vector<std::string>);
void remGraph(std::vector<std::string>);
void selGraph(std::vector<std::string>);
void addVertex(std::vector<std::string>);
void addEdge(std::vector<std::string>);
void remVertex(std::vector<std::string>);
void remEdge(std::vector<std::string>);
void graphBFS(std::vector<std::string>);
void graphDFS(std::vector<std::string>);
void graphMatrix(std::vector<std::string>);
void graphVector(std::vector<std::string>);
void graphPlot();
void back();
void list();
void error();
void noCommand();
void printError(std::string);
void printMessage(std::string);
void printWarning(std::string);
void help();
bool execmd(Command, std::vector<std::string>);
void mainTest();

int main(void) {
	bool running = true;

	graphs = readGraphData();

	if (DEBUG) running = false;
	curGraph = nullptr;

	printMessage("Disciplina de Grafos - Projeto 1\n");
	while (running) {
		std::cout << "cmd>";
		auto line = readConsole();
		auto tokens = scanner(line);
		auto command = parser(tokens);

		running = execmd(command, tokens);
	}

	if (DEBUG) mainTest();

	return EXIT_SUCCESS;
}

void addGraph(std::vector<std::string> param) {
	if (not curGraph) {
		for (size_t i = 0; i < graphs.size(); i++) {
			if (graphs[i].text._Equal(param[0])) {
				printError("Graph " + param[0] + " already exists.");
				return;
			}
		}
		graphs.push_back(Graph(param[0]));
		printMessage("Graph " + param[0] + " added.");
		return;
	}
	printError("It's not possible to add graphs here.");
}

void remGraph(std::vector<std::string> param) {
	if (not curGraph) {
		for (size_t i = 0; i < graphs.size(); i++) {
			if (graphs[i].text._Equal(param[0])) {
				graphs.erase(graphs.begin() + i);
				printMessage("Graph " + param[0] + " removed.");
				return;
			}
		}
		printError("Graph " + param[0] + " doesn't exists.");
		return;
	}
	printError("It's not possible to remove graphs here.");
}

void selGraph(std::vector<std::string> param) {
	if (not curGraph) {
		for (size_t i = 0; i < graphs.size(); i++) {
			if (graphs[i].text._Equal(param[0])) {
				curGraph = &graphs[i];
				printMessage("Graph " + param[0] + " selected.");
				return;
			}
		}
		printError("Graph " + param[0] + " doesn't exists.");
		return;

	}
	printError("It's not possible to select graphs here.");
}

void addVertex(std::vector<std::string> param) {
	if (curGraph) {
		if (param.size() == 1) {
			if (curGraph->addVertex(new Vertex(param[0]))) {
				printMessage("Vertex " + param[0] + " added.");
				return;
			}
		}
		if (param.size() == 3) {
			if (curGraph->addVertex(new Vertex(atoi(param[1].c_str()), atoi(param[2].c_str()), param[0]))) {
				printMessage("Vertex " + param[0] + " added.");
				return;
			}
		}
		printError("Vertex " + param[0] + " already exists.");
		return;
	}
	printError("No graph selected.");
}

void addEdge(std::vector<std::string> param) {
	if (curGraph) {
		if (param.size() == 2) {
			if (curGraph->addEdge(param[0], param[1])) {
				printMessage("Edge " + param[0] + "->" + param[1] + " added.");
				return;
			}
		}
		printError("Edge " + param[0] + "->" + param[1] + " already exists.");
		return;
	}
	printError("No graph selected.");
}

void remVertex(std::vector<std::string> param) {
	if (curGraph) {
		if (param.size() == 1) {
			if (curGraph->removeVertex(param[0])) {
				printMessage("Vertex " + param[0] + " removed.");
				return;
			}
		}
		printError("Vertex " + param[0] + " doesn't exists.");
		return;
	}
	printError("No graph selected.");
}

void remEdge(std::vector<std::string> param) {
	if (curGraph) {
		if (param.size() == 2) {
			if (curGraph->addEdge(param[0], param[1])) {
				printMessage("Edge " + param[0] + "->" + param[1] + " removed.");
				return;
			}
		}
		printError("Edge " + param[0] + "->" + param[1] + " doesn't exists.");
		return;
	}
	printError("No graph selected.");
}

void graphBFS(std::vector<std::string> param) {
	if (curGraph) {
		if (param.size() == 1) {
			auto vertex = curGraph->getVertex(param[0]);
			if (vertex) {
				curGraph->BFS(vertex);
				printMessage("");
				return;
			}
		}
		printError("Vertex " + param[0] + " doesn't exists.");
		return;
	}
	printError("No graph selected.");
}

void graphDFS(std::vector<std::string> param) {
	if (curGraph) {
		if (param.size() == 1) {
			auto vertex = curGraph->getVertex(param[0]);
			if (vertex) {
				curGraph->DFS(vertex);
				printMessage("");
				return;
			}
		}
		printError("Vertex " + param[0] + " doesn't exists.");
		return;
	}
	printError("No graph selected.");
}

void graphMatrix(std::vector<std::string> param) {
	if (curGraph) {
		printAdjacencyMatrix(curGraph->getMatrix(), curGraph->vertices.size(), curGraph->vertices, curGraph->text);
		return;
	}
	printError("No graph selected.");
}

void graphVector(std::vector<std::string> param) {
	if (curGraph) {
		printAdjacencyVector(curGraph->getVector(), curGraph->text);
		return;
	}
	printError("No graph selected.");
}

void graphPlot() {
	if (curGraph) {
		plotGraph(*curGraph);
		return;
	}
	printError("No graph selected.");
}

void back() {
	if (curGraph) {
		curGraph = nullptr;
		return;
	}
	printError("No graph selected.");
}

void list() {
	if (not curGraph) {
		for (auto g : graphs) {
			std::cout << "Graph: " << g.text << std::endl;
		}
		std::cout << std::endl;
		return;
	}
	printError("It's not possible to list the graphs here.");
}

void error() {
	printError("There was an error processing the command.");
}

void noCommand() {
	printError("No commands found.");
}

void printError(std::string msg) {
	std::cout << "ERROR: " << msg << std::endl << std::endl;
}

void printWarning(std::string msg) {
	std::cout << "Warning: " << msg << std::endl << std::endl;
}

void printMessage(std::string msg) {
	std::cout << msg << std::endl << std::endl;
}

void help() {
	std::string msg = "";
	msg += "\n";
	msg += "add graph {name}              Adds a new graph\n";
	msg += "rem graph {name}              Removes a graph\n";
	msg += "sel graph {name}              Select a graph and move the application to Graph level\n";
	msg += "cls                           Clean the console\n";
	msg += "list                          List all graphs\n";
	msg += "exit                          Close the application\n\n";
	msg += "add vertex {id} {x} {y}       Graph level: Adds a new vertex (params x and y are optional)\n";
	msg += "rem vertex {id}               Graph level: Removes a vertex\n";
	msg += "add edge {id1} {id2}          Graph level: Adds a new edge\n";
	msg += "rem edge {id1} {id2}          Graph level: Removes a edge\n";
	msg += "bfs {id}                      Graph level: Make a breadth-first search (busca em largura)\n";
	msg += "dfs {id}                      Graph level: Make a depth-first search (busca em profundidade)\n";
	msg += "matrix                        Graph level: Print the graph adjacency matrix\n";
	msg += "vector                        Graph level: Print the graph adjacency vector\n";
	msg += "plot                          Graph level: Draw the graph on a graphic window\n";
	msg += "back                          Graph level: Exits of current graph\n\n";
	printMessage(msg);
}

bool execmd(Command command, std::vector<std::string> tokens) {
	switch (command) {
	case e_ADD_GRAPH:
		addGraph(tokens);
		break;
	case e_REM_GRAPH:
		remGraph(tokens);
		break;
	case e_SEL_GRAPH:
		selGraph(tokens);
		break;
	case e_ADD_VERTEX:
		addVertex(tokens);
		break;
	case e_ADD_EDGE:
		addEdge(tokens);
		break;
	case e_REM_VERTEX:
		remVertex(tokens);
		break;
	case e_REM_EDGE:
		remEdge(tokens);
		break;
	case e_BFS:
		graphBFS(tokens);
		break;
	case e_DFS:
		graphDFS(tokens);
		break;
	case e_MATRIX:
		graphMatrix(tokens);
		break;
	case e_VECTOR:
		graphVector(tokens);
		break;
	case e_PLOT:
		graphPlot();
		break;
	case e_BACK:
		back();
		break;
	case e_LIST:
		list();
		break;
	case e_EXIT:
		return false;
		break;
	case e_ERROR:
		error();
		break;
	case e_HELP:
		help();
		break;
	case e_CLS:
		system("cls");
		break;
	case e_NOCOMMAND:
		noCommand();
		break;
	}
	return true;
}

void mainTest() {

	//loadPrintTest(graphs);
	int NGrafo = 10;

	//graphs[NGrafo].DFS(graphs[NGrafo].getVertex("a"));
	curGraph = &graphs[NGrafo];

	printAdjacencyMatrix(curGraph->getMatrix(), curGraph->vertices.size(), curGraph->vertices, curGraph->text);
	//graphs[NGrafo].indirectTransitiveClosure(graphs[NGrafo].getVertex("a"));

	//loadPrintTest(graphs);
	//plotGraph(graphs[5]);
	//loadPrintTest(graphs);
	//graphs[4].BFS(graphs[4].getVertex("a"));
	//testGraph();

}
