#include <bits/stdc++.h>
#include "Tester.hpp"
using namespace std;

vector <pair <int, double>> Tester(void (*f)(int [], int), int vmax, string name)
{
    const double Tmax = 2;
    vector <pair <int, double>> ans;
    uniform_int_distribution <int> dist(0, vmax);

    cerr << "Starting benchmark for " + name << endl;

    for (int l = 1; l <= (int)1e9; l *= 2) {
        vector <int> v(l);
        for_each(v.begin(), v.end(), [&](int & it) { it = dist(rnd); });
        auto w = v;
        cerr << " Starting sorting ...";
        cerr.flush();
        auto before = chrono::high_resolution_clock::now();
        (*f)(v.data(), l);
        auto after = chrono::high_resolution_clock::now();
        cerr << " Done." << endl;
        double duration = chrono::duration_cast <chrono::nanoseconds> (after - before).count() / 1e9;
        
        sort(w.begin(), w.end());
        if (w != v)
            throw runtime_error("Function wasn't able to properly sort vector v");
        ans.push_back({ l, duration });
        cerr << "  Sorted array of length " << l << " in " << duration << " seconds.\n";
        if (duration > Tmax)
            break;
    }
    return ans;
}