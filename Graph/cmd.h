#pragma once

#include <iostream>
#include <vector>
#include <string>

const std::string c_ADD = "add";
const std::string c_REM = "rem";
const std::string c_SEL = "sel";
const std::string c_EXIT = "exit";

const std::string c_GRAPH = "graph";
const std::string c_VERTEX = "vertex";
const std::string c_EDGE = "edge";
const std::string c_BFS = "bfs";
const std::string c_DFS = "dfs";
const std::string c_PLOT = "plot";
const std::string c_BACK = "back";

typedef short Command;

enum CommandCodes {
	e_NOCOMMAND,
	e_ERROR,
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
	e_PLOT,
	e_BACK
};

std::string TOKENS[] = {
	c_ADD,
	c_REM,
	c_SEL,
	c_EXIT,
	c_GRAPH,
	c_VERTEX,
	c_EDGE,
	c_BFS,
	c_DFS,
	c_PLOT,
	c_BACK
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
	return tokens;
}

Command parser(std::vector<std::string> &tokens) {
	if (tokens.size() == 0) {
		return e_NOCOMMAND;
	}
	if (tokens.size() > 1) {
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
		if (tokens[0]._Equal(c_REM) and tokens[1]._Equal(c_VERTEX)) {
			return e_REM_VERTEX;
		}
		if (tokens[0]._Equal(c_REM) and tokens[1]._Equal(c_EDGE)) {
			return e_REM_EDGE;
		}
	}
	if (tokens[0]._Equal(c_EXIT)) {
		return e_EXIT;
	}
	if (tokens[0]._Equal(c_BFS)) {
		return e_BFS;
	}
	if (tokens[0]._Equal(c_DFS)) {
		return e_DFS;
	}
	if (tokens[0]._Equal(c_PLOT)) {
		return e_PLOT;
	}
	if (tokens[0]._Equal(c_BACK)) {
		return e_BACK;
	}
	return e_ERROR;
}
