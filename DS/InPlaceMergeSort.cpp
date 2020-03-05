// https://xinok.wordpress.com/2014/08/17/in-place-merge-sort-demystified-2/
#include <bits/stdc++.h>
using namespace std;
BUSITA


namespace InPlaceMergeSort {
    using T = int;

    void Interclasare(T * v, int n, T * w, int m)
    {   
        if (n > m) {
            if (v[0] > w[0])
                swap(v[0], w[0]);
            v++, n--;
        }
        else if (n < m) {
            if (w[m - 1] < v[n - 1])
                swap(w[m - 1], v[n - 1]);
            m--;
        }

        assert(n == m);

        if (n == 1) {
            if (v[0] > w[0])
                swap(v[0], w[0]);
            return;
        }

        int count = n / 2; /// cate mut din v in w si vice versa
        /// primul element mutat din v este v[n - count]
        /// ultimul element mutat din w este v[count - 1]

        for (int i = 0; i < count; i++)
            swap(v[n - count + i], w[i]);

        Interclasare(v, n - count, v + n - count, count);
        Interclasare(w, count, w + count, m - count);
    }

    void MergeSort(T * v, int n)
    {
        if (n <= 1)
            return;

        int half = n / 2;

        MergeSort(v, half);
        MergeSort(v + half, n - half);

        cerr << "Before interclasare: ";
        for (int i = 0; i < n; i++)
            cerr << v[i] << ' ';
        cerr << '\n';
        Interclasare(v, half, v + half, n - half);
        cerr << "After interclasare: ";
        for (int i = 0; i < n; i++)
            cerr << v[i] << ' ';
        cerr << '\n';
    }
}

int main()
{
    vector <int> v = { 5, 4, 3, 2, 1 };

    InPlaceMergeSort::MergeSort(v.data(), v.size());

    for (auto i : v)
        cerr << i << ' ';

    cerr << '\n';
    return 0;
    mt19937 rnd(time(0));

    while (1) {
        int sz = rnd() % 100 + 1;
        vector <int> v(sz);

        for (auto & i : v)
            i = rnd() % 1000;

        vector <int> w = v;
        sort(w.begin(), w.end());
        InPlaceMergeSort::MergeSort(v.data(), v.size());

        if (w != v) {
            cerr << "WA\n";
            for (auto i : v)
                cerr << i << ' ';
            cerr << endl;
            return 0;
        }
        else
            cerr << "OK ";
    }

    return 0;
}