#ifndef _SkipListSort
#define _SkipListSort

#include <random>
extern std::mt19937 rnd;

/**
 * create-a-skip-list-and-sort-a-vector-with-it sort algorithm
 * 
 * Memory: O(n * log(n))
 * Time:   O(n * log(n))
 */

void SkipListSort(int [], int);

#endif // _SkipListSort
