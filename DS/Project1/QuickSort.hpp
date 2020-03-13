#ifndef _QuickSort
#define _QuickSort

/**
 * Simple quick sort algorithm
 * 
 * Memory: O(n) - inplace
 * Time:   O(n * log(n)) expected
 */


#include <random>
extern std::mt19937 rnd;

void QuickSort(int [], int);

#endif // _QuickSort
