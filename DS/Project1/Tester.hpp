#ifndef _Tester
#define _Tester

#include <random>
#include <map>
#include <vector>

extern std::mt19937 rnd;

std::vector <std::pair <int, double>> Tester(void (*)(int [], int), int, std::string="function");

#endif // _Tester
