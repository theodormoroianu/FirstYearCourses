#include <bits/stdc++.h>
#include "BubbleSort.hpp"
using namespace std;

void BubbleSort(int v[], int n)
{
    bool done = 0;
    while (!done) {
        done = 1;
        for (int i = 0; i < n - 1; i++)
            if (v[i] > v[i + 1])
                swap(v[i], v[i + 1]), done = 0;
    }
}
