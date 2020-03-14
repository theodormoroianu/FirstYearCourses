#include <bits/stdc++.h>
#include "Tester.hpp"
#include "SkipList.hpp"
#include "CountSort.hpp"
#include "MergeSort.hpp"
#include "QuickSort.hpp"
#include "BubbleSort.hpp"
#include "RadixSort.hpp"
#include "HeapSort.hpp"
#include "TreapSort.hpp"
#include "AVLSort.hpp"
using namespace std;

vector <pair <void(*)(int[], int), string>> functions = {
    { SkipListSort, "SkipListSort" },
    { CountSort,    "CountSort" },
    { MergeSort,    "MergeSort" },
    { QuickSort,    "QuickSort" },
    { BubbleSort,   "BubbleSort" },
    { RadixSort,    "RadixSort" },
    { HeapSort,     "HeapSort" },
    { TreapSort,    "TreapSort" },
    { AVLSort,      "AVLSort" }
};

void Benchmark()
{
    /// VMAX is maximal value of an element. Change it for checking functions like CountSort or RadixSort 
    int VMAX = 10000000;
    /// TMAX is maximal time allowed for a sorting function
    double TMAX = 0.5;
    int n_max = 0;

    vector <vector <double>> results;
    for (auto it : functions) {
        cout << "Starting benchmark for " + it.second + " ...   ";
        cout.flush();

        results.push_back(Tester(it.first, VMAX, TMAX));
        cout << "Done" << endl;
        n_max = max(n_max, (int)results.back().size());
    }

    for (int l = 10; l < n_max; l += 2) {
        cout << "\n\nFor a length of " << (1 << l) << " (2 ^ " << l << "), sorting algorithms took:\n";
        for (int i = 0; i < (int)results.size(); i++) {
            cout << "   " << i + 1 << ". " << functions[i].second << ":   ";
            if (l < (int)results[i].size())
                cout << results[i][l] << " seconds" << endl;
            else
                cout << "> " << TMAX << " seconds" << endl;
        }
    }
}

int main()
{
    // auto x = Tester(AVLSort, 1000);

    // for (auto i : x)
    //     cerr << i << ' ';
    // return 0;
    Benchmark();

    return 0;
}
