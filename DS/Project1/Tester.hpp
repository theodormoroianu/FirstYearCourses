#ifndef _Tester
#define _Tester

/**
 * Testing function that receives a pointer to a sorting function and returns
 * time for sorting vectors until the time limit
 */

#include <random>
#include <map>
#include <vector>

std::vector <double> Tester(void (*)(int [], int), int, double = 2.);

#endif // _Tester
