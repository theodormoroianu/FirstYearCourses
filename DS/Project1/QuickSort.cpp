#include <bits/stdc++.h>
#include "QuickSort.hpp"
using namespace std;

namespace {
    mt19937 rnd(time(0));
}

void QuickSort(int v[], int n)
{
    if (n <= 1)
        return;
    int poz = rnd() % n;
    swap(v[poz], v[n - 1]);
    poz = 0;
    for (int i = 0; i < n - 1; i++) {
        if (v[i] < v[n - 1] || (v[i] == v[n - 1] && rnd() % 2 == 0)) {
            swap(v[i], v[poz]);
            poz++;
        }
    }
    swap(v[n - 1], v[poz]);
    QuickSort(v, poz);
    QuickSort(v + poz + 1, n - poz - 1);
}
