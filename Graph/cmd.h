#pragma once

#include <iostream>
#include <vector>
#include <string>

const std::string ADD = "add";
const std::string REM = "rem";
const std::string SEL = "sel";
const std::string EXIT = "exit";

const std::string GRAPH = "graph";
const std::string VERTEX = "vertex";
const std::string EDGE = "edge";
const std::string BFS = "bfs";
const std::string DFS = "dfs";
const std::string PLOT = "plot";
const std::string BACK = "back";

std::string TOKENS[] = {
	ADD,
	REM,
	SEL,
	EXIT,
	GRAPH,
	VERTEX,
	EDGE,
	BFS,
	DFS,
	PLOT,
	BACK
};

std::string COMMANDS[][2] = {
	{ ADD, GRAPH },
	{ REM, GRAPH },
	{ SEL, GRAPH },
	{ EXIT },
	{ ADD, VERTEX },
	{ ADD, EDGE },
	{ REM, VERTEX },
	{ REM, EDGE },
	{ BFS },
	{ DFS },
	{ PLOT },
	{ BACK }
};

bool isToken(std::string str) {
	for (auto t : TOKENS) {
		if (str._Equal(t)) {
			return true;
		}
	}
	return false;
}

std::string readConsole() {
	std::string line;
	std::getline(std::cin, line);
	return line;
}

std::vector<std::string> scanner(std::string line) {
	auto tokens = std::vector<std::string>();
	std::string word = "";
	for (auto c : line) {
		word += c;
		if (isToken(word)) {
			tokens.push_back(word);
			word = "";
		}
	}
}

