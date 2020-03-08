#include <bits/stdc++.h>
#include "RadixSort.hpp"
using namespace std;

void RadixSort(int v[], int n)
{
    const int BASE = 100000;
    vector <vector <int>> dump(BASE);
    
    for (int p_act = 1, need = 1; (need ^= 1) == 0; p_act *= BASE) {
        for (int i = 0; i < n; i++) {
            dump[(v[i] / p_act) % BASE].push_back(v[i]);
            need |= (v[i] / p_act >= BASE);
        }
        int n = 0;
        for (int i = 0; i < BASE; i++) {
            copy(dump[i].begin(), dump[i].end(), v + n);
            n += dump[i].size();
            dump[i].clear();
        }
    }
}
