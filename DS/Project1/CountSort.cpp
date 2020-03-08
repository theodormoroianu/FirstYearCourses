#include <bits/stdc++.h>
#include "CountSort.hpp"
using namespace std;

void CountSort(int v[], int n)
{
    int vmin = 1e9, vmax = -1e9;
    for (int i = 0; i < n; i++)
        vmin = min(vmin, v[i]), vmax = max(vmax, v[i]);

    if (vmax - vmin > 5e7)
        throw length_error("Pentru CountSort ar fi nevoie de un vector de lungime "
                + to_string(vmax - vmin) + " ceea ce depaseste MAX_SIZE");

    vector <int> c(vmax - vmin + 1, 0);

    for (int i = 0; i < n; i++)
        c[v[i] - vmin]++;

    int cnt = 0;
    for (int i = 0; i < vmax - vmin + 1; i++)
        while (c[i]--)
            v[cnt++] = i + vmin;

    assert(cnt == n);
}
