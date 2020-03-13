#include "HeapSort.hpp"
#include <bits/stdc++.h>
using namespace std;

void HeapSort(int v[], int N)
{
    int dim_heap = N;

    auto val_at = [&](int x) {
        return (x < dim_heap ? v[x] : -1e9);
    };

    auto push_down = [&](int poz) {
        while (1) {
            int f1 = val_at(2 * poz + 1);
            int f2 = val_at(2 * poz + 2);
            if (v[poz] >= max(f1, f2))
                return;
            if (f1 >= f2)
                swap(v[poz], v[2 * poz + 1]), poz = 2 * poz + 1;
            else
                swap(v[poz], v[2 * poz + 2]), poz = 2 * poz + 2;    
        }
    };

    for (int i = N - 1; i >= 0; i--)
        push_down(i);

    for (int i = N - 1; i >= 0; i--) {
        push_down(0);
        swap(v[0], v[--dim_heap]);
    }
}