#include <iostream>
#include "test.h"
#include "graph.h"
#include "cmd.h"
#include "util.h"
#include "plot.h"

#define DEBUG true

std::vector<Graph> graphs;
Graph* curGraph;
std::string language;

void setLanguage(std::vector<std::string>);
void setLanguage();
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
void printError(std::string, std::string);
void printMessage(std::string, std::string);
void printWarning(std::string, std::string);
void help();
bool execmd(Command, std::vector<std::string>);
void mainTest();

int main(void) {
	setlocale(LC_ALL, "Portuguese");
	bool running = true;

	graphs = readGraphData();

	if (DEBUG) running = false;
	curGraph = nullptr;
	language = "en-us";

	setLanguage();
	printMessage("\nDisciplina de Grafos - Projeto 1", "\nGraph Class - Project 1");
	printMessage("Para mais detalhes digite help.", "For more details type help.");

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
				printError("Grafo " + param[0] + " já existe.", "Graph " + param[0] + " already exists.");
				return;
			}
		}
		graphs.push_back(Graph(param[0]));
		printMessage("Grafo " + param[0] + " adicionado.", "Graph " + param[0] + " added.");
		return;
	}
	printError("Não é possível adicionar um grafo aqui.", "It's not possible to add graphs here.");
}

void remGraph(std::vector<std::string> param) {
	if (not curGraph) {
		for (size_t i = 0; i < graphs.size(); i++) {
			if (graphs[i].text._Equal(param[0])) {
				graphs.erase(graphs.begin() + i);
				printMessage("Grafo " + param[0] + " removido.", "Graph " + param[0] + " removed.");
				return;
			}
		}
		printError("Grafo " + param[0] + " não existe.", "Graph " + param[0] + " doesn't exists.");
		return;
	}
	printError("Não é possivel remover esse grafo.", "It's not possible to remove graphs here.");
}

void selGraph(std::vector<std::string> param) {
	if (not curGraph) {
		for (size_t i = 0; i < graphs.size(); i++) {
			if (graphs[i].text._Equal(param[0])) {
				curGraph = &graphs[i];
				printMessage("Grafo " + param[0] + " selecionado.", "Graph " + param[0] + " selected.");
				return;
			}
		}
		printError("Grafo " + param[0] + " não existe.", "Graph " + param[0] + " doesn't exists.");
		return;

	}
	printError("Não é possível selecionar esse grafo.", "It's not possible to select graphs here.");
}

void addVertex(std::vector<std::string> param) {
	if (curGraph) {
		if (param.size() == 1) {
			if (curGraph->addVertex(new Vertex(param[0]))) {
				printMessage("Vertice " + param[0] + " adicionado.", "Vertex " + param[0] + " added.");
				return;
			}
		}
		if (param.size() == 3) {
			if (curGraph->addVertex(new Vertex(atoi(param[1].c_str()), atoi(param[2].c_str()), param[0]))) {
				printMessage("Vertice " + param[0] + " adicionado.", "Vertex " + param[0] + " added.");
				return;
			}
		}
		printError("Vertice " + param[0] + " já existe.", "Vertex " + param[0] + " already exists.");
		return;
	}
	printError("Grafo não selecionado", "No graph selected.");
}

void addEdge(std::vector<std::string> param) {
	if (curGraph) {
		if (param.size() == 2) {
			if (curGraph->addEdge(param[0], param[1])) {
				printMessage("Aresta " + param[0] + "->" + param[1] + " adicionado.", "Edge " + param[0] + "->" + param[1] + " added.");
				return;
			}
		}
		printError("Aresta " + param[0] + "->" + param[1] + " já existe.", "Edge " + param[0] + "->" + param[1] + " already exists.");
		return;
	}
	printError("Grafo não selecionado.", "No graph selected.");
}

void remVertex(std::vector<std::string> param) {
	if (curGraph) {
		if (param.size() == 1) {
			if (curGraph->removeVertex(param[0])) {
				printMessage("Vertice " + param[0] + " removido.", "Vertex " + param[0] + " removed.");
				return;
			}
		}
		printError("Vertice " + param[0] + " não existe.", "Vertex " + param[0] + " doesn't exists.");
		return;
	}
	printError("Grafo não selecionado.", "No graph selected.");
}

void remEdge(std::vector<std::string> param) {
	if (curGraph) {
		if (param.size() == 2) {
			if (curGraph->addEdge(param[0], param[1])) {
				printMessage("Aresta " + param[0] + "->" + param[1] + " removido.", "Edge " + param[0] + "->" + param[1] + " removed.");
				return;
			}
		}
		printError("Aresta " + param[0] + "->" + param[1] + " não existe.", "Edge " + param[0] + "->" + param[1] + " doesn't exists.");
		return;
	}
	printError("Grafo não selecionado.", "No graph selected.");
}

void graphBFS(std::vector<std::string> param) {
	if (curGraph) {
		if (param.size() == 1) {
			auto vertex = curGraph->getVertex(param[0]);
			if (vertex) {
				curGraph->BFS(vertex);
				return;
			}
		}
		printError("Vertice " + param[0] + " não existe.", "Vertex " + param[0] + " doesn't exists.");
		return;
	}
	printError("Grafo não selecionado.", "No graph selected.");
}

void graphDFS(std::vector<std::string> param) {
	if (curGraph) {
		if (param.size() == 1) {
			auto vertex = curGraph->getVertex(param[0]);
			if (vertex) {
				curGraph->DFS(vertex);
				return;
			}
		}
		printError("Vertice " + param[0] + " não existe.", "Vertex " + param[0] + " doesn't exists.");
		return;
	}
	printError("Grafo não selecionado.", "No graph selected.");
}

void graphMatrix(std::vector<std::string> param) {
	if (curGraph) {
		printAdjacencyMatrix(curGraph->getMatrix(), curGraph->vertices.size(), curGraph->vertices, curGraph->text);
		return;
	}
	printError("Grafo não selecionado.", "No graph selected.");
}

void graphVector(std::vector<std::string> param) {
	if (curGraph) {
		printAdjacencyVector(curGraph->getVector(), curGraph->text);
		return;
	}
	printError("Grafo não selecionado.", "No graph selected.");
}

void graphPlot() {
	if (curGraph) {
		plotGraph(*curGraph);
		return;
	}
	printError("Grafo não selecionado.", "No graph selected.");
}

void back() {
	if (curGraph) {
		curGraph = nullptr;
		return;
	}
	printError("Grafo não selecionado.", "No graph selected.");
}

void list() {
	if (not curGraph) {
		for (auto g : graphs) {
			std::cout << "Graph: " << g.text << std::endl;
		}
		std::cout << std::endl;
		return;
	}
	printError("Não é possivel listar o grafo aqui.", "It's not possible to list the graphs here.");
}

void error() {
	printError("Ocorreu um erro ao executar o comando.", "There was an error processing the command.");
}

void noCommand() {
	printError("Comando não encontrado.", "No commands found.");
}

void printError(std::string msgPT, std::string msgEN) {
	if(language._Equal("pt-br"))
		std::cout << "ERRO: " << msgPT << std::endl << std::endl;
	else
		std::cout << "ERROR: " << msgEN << std::endl << std::endl;
}

void printWarning(std::string msgPT, std::string msgEN) {
	if (language._Equal("pt-br"))
		std::cout << "Aviso: " << msgPT << std::endl << std::endl;
	else
		std::cout << "Warning: " << msgEN << std::endl << std::endl;
}

void printMessage(std::string msgPT, std::string msgEN) {
	if (language._Equal("pt-br"))
		std::cout << msgPT << std::endl << std::endl;
	else
		std::cout << msgEN << std::endl << std::endl;
}

void setLanguage(std::vector<std::string> params) {
	if(params[0]._Equal("pt-br") || params[0]._Equal("en-us"))
		language = params[0];
	else
		printError("You need select pt-br or en-us as the main language.", "You need select pt-br or en-us as the main language.");
}

void setLanguage() {
	while (true) {
		std::cout << "Choose the interface language (pt-br or en-us):\n";
		std::cin >> language;
		if (language._Equal("pt-br")) {
			language = "pt-br";
			break;
		}
		else if (language._Equal("en-us")) {
			language = "en-us";
			break;
		}

		std::cout << std::endl;
		printError("You need select pt-br or en-us as the main language.", "You need select pt-br or en-us as the main language.");
	}
	printMessage("Alterado.", "Changed.");
	readConsole();
}

void help() {
	std::string msg = "";
	msg += "\n";
	if (language._Equal("pt-br")) {
		msg += "add graph {name}                  Adiciona um novo grafo.\n";
		msg += "rem graph {name}                  Remove um grafo.\n";
		msg += "sel graph {name}                  Seleciona um grafo e move para nivel de grafo.\n";
		msg += "cls                               Limpa o console.\n";
		msg += "list                              Lista os grafos.\n";
		msg += "lang pt-br|en-us                  Muda o idioma.\n";
		msg += "exit                              Fecha a aplicação.\n\n";
		msg += "add vertex {id} [o]{x} [o]{y}     Grafo level: Adiciona um novo vertice.\n";
		msg += "rem vertex {id}                   Grafo level: Remove um vertice.\n";
		msg += "add edge {id1} {id2}              Grafo level: Adiciona uma nova aresta.\n";
		msg += "rem edge {id1} {id2}              Grafo level: Remove uma aresta.\n";
		msg += "bfs {id}                          Grafo level: Realiza a busca em largura (BFS).\n";
		msg += "dfs {id}                          Grafo level: Realiza a busca em profundidade (DFS).\n";
		msg += "plot                              Grafo level: Desenha o grafo em uma janela gráfica.\n";
		msg += "back                              Grafo level: Sai do grafo atual.\n";
	}
	else {
		msg += "add graph {name}                  Adds a new graph.\n";
		msg += "rem graph {name}                  Removes a graph.\n";
		msg += "sel graph {name}                  Select a graph and move the application to Graph level.\n";
		msg += "cls                               Clean the console.\n";
		msg += "list                              List graphs.\n";
		msg += "lang pt-br|en-us                  Changes language.\n";
		msg += "exit                              Close the application.\n\n";
		msg += "add vertex {id} [o]{x} [o]{y}     Graph level: Adds a new vertex.\n";
		msg += "rem vertex {id}                   Graph level: Removes a vertex.\n";
		msg += "add edge {id1} {id2}              Graph level: Adds a new edge.\n";
		msg += "rem edge {id1} {id2}              Graph level: Removes a edge.\n";
		msg += "bfs {id}                          Graph level: Make a breadth-first search (BFS).\n";
		msg += "dfs {id}                          Graph level: Make a depth-first search (DFS).\n";
		msg += "plot                              Graph level: Draw the graph on a graphic window.\n";
		msg += "back                              Graph level: Exits of current graph.\n";
	}

	printMessage(msg, msg);
}

bool execmd(Command command, std::vector<std::string> tokens) {
	switch (command) {
	case e_LANG:
		setLanguage(tokens);
		break;
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

	std::cout << std::endl << std::endl;
	if (graphs[NGrafo].isConnectivity())
		std::cout << "O grafo informado é conexo";
	else
		std::cout << "O grafo informado não é conexo";

	//loadPrintTest(graphs);
	//plotGraph(graphs[5]);
	//loadPrintTest(graphs);
	//graphs[4].BFS(graphs[4].getVertex("a"));
	//testGraph();

}
