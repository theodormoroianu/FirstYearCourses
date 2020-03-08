#ifndef _Sortari
#define _Sortari

#include <random>
#include <map>
#include <vector>
#include "SkipList.hpp"
#include "CountSort.hpp"
#include "MergeSort.hpp"
#include "QuickSort.hpp"
#include "BubbleSort.hpp"

std::mt19937 rnd(time(0));
const double Tmax = 2;

std::map <std::string, std::vector <std::pair <int, double>>> Evaluate(std::vector <void (*)(int[], int)>, int n);

#endif // _Sortari
