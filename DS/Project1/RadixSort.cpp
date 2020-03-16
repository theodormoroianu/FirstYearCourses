#include <bits/stdc++.h>
#include "RadixSort.hpp"
using namespace std;

void RadixSort(int v[], int n)
{
    const int BASE = (1 << 17), LG = 17;
    vector <int> head(BASE);
    vector <pair <int, int>> lst(n);

    for (int _ = 0, shift = 0; _ < 2; _++, shift += LG) {
        fill(head.begin(), head.end(), -1);
        for (int i = 0; i < n; i++) {
            lst[i] = { v[i], i };
            swap(lst[i].second, head[(v[i] >> shift) & (BASE - 1)]);
        }
        int n = 0;
        for (int i = BASE - 1; i >= 0; i--)
            for (int j = head[i]; j != -1; j = lst[j].second)
                v[n++] = lst[j].first;
        
        reverse(v, v + n);
    }
}
