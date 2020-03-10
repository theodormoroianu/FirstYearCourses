#include <iostream>
#include "Tester.hpp"
#include "SkipList.hpp"
#include "CountSort.hpp"
#include "MergeSort.hpp"
#include "QuickSort.hpp"
#include "BubbleSort.hpp"
#include "RadixSort.hpp"
using namespace std;

mt19937 rnd(time(0));

int main()
{
    auto v = Tester(QuickSort, 1000000, "QuickSort");

    cout << "Benchmarks:\n";
    for (auto i : v)
        cout << "For n = " << i.first << ", QuickSort took " << i.second << " second\n";

    return 0;
}
