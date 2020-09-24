#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string, char);

std::string trim(std::string);

double clamp(double, double, double);

#endif // UTIL_H
