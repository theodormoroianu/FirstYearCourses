#include <bits/stdc++.h>
#include "MergeSort.hpp"
using namespace std;

void MergeSort(int v[], int n)
{
    if (n <= 1)
        return;
    int mij = n / 2;
    MergeSort(v, mij);
    MergeSort(v + mij, n - mij);

    vector <int> to_replace;
    merge(v, v + mij, v + mij, v + n, back_inserter(to_replace));
    copy(to_replace.begin(), to_replace.end(), v);
}
