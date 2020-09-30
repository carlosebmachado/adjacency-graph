#pragma once

#include <iostream>
#include <vector>
#include <string>

const char* c_ADD = "add";
const char* c_REM = "rem";
const char* c_SEL = "sel";
const char* c_CLS = "cls";
const char* c_LIST = "list";
const char* c_EXIT = "exit";

const char* c_GRAPH = "graph";
const char* c_VERTEX = "vertex";
const char* c_EDGE = "edge";
const char* c_BFS = "bfs";
const char* c_DFS = "dfs";
const char* c_MATRIX = "matrix";
const char* c_VECTOR = "vector";
const char* c_PLOT = "plot";
const char* c_BACK = "back";
const char* c_HELP = "help";

typedef short Command;

enum CommandCodes {
	e_NOCOMMAND,
	e_ERROR,
	e_HELP,
	e_CLS,
	e_LIST,
	e_ADD_GRAPH,
	e_REM_GRAPH,
	e_SEL_GRAPH,
	e_EXIT,
	e_ADD_VERTEX,
	e_ADD_EDGE,
	e_REM_VERTEX,
	e_REM_EDGE,
	e_BFS,
	e_DFS,
	e_MATRIX,
	e_VECTOR,
	e_PLOT,
	e_BACK
};

const char* TOKENS[] = {
	c_ADD,
	c_REM,
	c_SEL,
	c_EXIT,
	c_LIST,
	c_GRAPH,
	c_VERTEX,
	c_EDGE,
	c_BFS,
	c_DFS,
	c_MATRIX,
	c_VECTOR,
	c_PLOT,
	c_BACK,
	c_HELP,
	c_CLS
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
	std::transform(line.begin(), line.end(), line.begin(), [](unsigned char c) { return std::tolower(c); });
	line += " ";
	return line;
}

std::vector<std::string> scanner(std::string line) {
	auto tokens = std::vector<std::string>();
	std::string word = "";
	for (auto c : line) {
		if (isToken(word) or c == ' ') {
			tokens.push_back(word);
			word = "";
			continue;
		}
		word += c;
	}
	return tokens;
}

Command parser(std::vector<std::string>& tokens) {
	if (tokens.size() == 0) {
		return e_NOCOMMAND;
	}
	if (tokens.size() == 1) {
		if (tokens[0]._Equal(c_EXIT)) {
			return e_EXIT;
		}
		if (tokens[0]._Equal(c_PLOT)) {
			return e_PLOT;
		}
		if (tokens[0]._Equal(c_BACK)) {
			return e_BACK;
		}
		if (tokens[0]._Equal(c_HELP)) {
			return e_HELP;
		}
		if (tokens[0]._Equal(c_CLS)) {
			return e_CLS;
		}
		if (tokens[0]._Equal(c_LIST)) {
			return e_LIST;
		}
		if (tokens[0]._Equal(c_MATRIX)) {
			tokens.erase(tokens.begin());
			return e_MATRIX;
		}
		if (tokens[0]._Equal(c_VECTOR)) {
			tokens.erase(tokens.begin());
			return e_VECTOR;
		}
	}
	if (tokens.size() == 2) {
		if (tokens[0]._Equal(c_BFS)) {
			tokens.erase(tokens.begin());
			return e_BFS;
		}
		if (tokens[0]._Equal(c_DFS)) {
			tokens.erase(tokens.begin());
			return e_DFS;
		}
	}
	if (tokens.size() > 2) {
		if (tokens.size() == 3 and tokens[0]._Equal(c_SEL) and tokens[1]._Equal(c_GRAPH)) {
			for (size_t i = 0; i < 2; i++) tokens.erase(tokens.begin());
			return e_SEL_GRAPH;
		}
		if (tokens.size() == 3 and tokens[0]._Equal(c_ADD) and tokens[1]._Equal(c_GRAPH)) {
			for (size_t i = 0; i < 2; i++) tokens.erase(tokens.begin());
			return e_ADD_GRAPH;
		}
		if (tokens.size() == 3 and tokens[0]._Equal(c_REM) and tokens[1]._Equal(c_GRAPH)) {
			for (size_t i = 0; i < 2; i++) tokens.erase(tokens.begin());
			return e_REM_GRAPH;
		}
		if ((tokens.size() == 3 or tokens.size() == 5) and tokens[0]._Equal(c_ADD) and tokens[1]._Equal(c_VERTEX)) {
			for (size_t i = 0; i < 2; i++) tokens.erase(tokens.begin());
			if (tokens.size() == 5)
				for (size_t i = 0; i < 2; i++) tokens.erase(tokens.begin());
			return e_ADD_VERTEX;
		}
		if (tokens.size() == 4 and tokens[0]._Equal(c_ADD) and tokens[1]._Equal(c_EDGE)) {
			for (size_t i = 0; i < 2; i++) tokens.erase(tokens.begin());
			return e_ADD_EDGE;
		}
		if (tokens.size() == 3 and tokens[0]._Equal(c_REM) and tokens[1]._Equal(c_VERTEX)) {
			for (size_t i = 0; i < 2; i++) tokens.erase(tokens.begin());
			return e_REM_VERTEX;
		}
		if (tokens.size() == 4 and tokens[0]._Equal(c_REM) and tokens[1]._Equal(c_EDGE)) {
			for (size_t i = 0; i < 2; i++) tokens.erase(tokens.begin());
			return e_REM_EDGE;
		}
	}
	return e_ERROR;
}
