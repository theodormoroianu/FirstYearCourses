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
#include "SplayTreeSort.hpp"
using namespace std;

void standard_sort(int v[], int n)
{
    sort(v, v + n);
}

vector <pair <void(*)(int[], int), string>> functions = {
    { SkipListSort,   "SkipListSort" },
    { CountSort,      "CountSort" },
    { MergeSort,      "MergeSort" },
    { QuickSort,      "QuickSort" },
    { BubbleSort,     "BubbleSort" },
    { RadixSort,      "RadixSort" },
    { HeapSort,       "HeapSort" },
    { TreapSort,      "TreapSort" },
    { AVLSort,        "AVLSort" },
    { SplayTreeSort,  "SplayTreeSort" },
    { standard_sort,  "STLSort" }
};

void Benchmark(int VMAX, double TMAX)
{
    int n_max = 0;

    vector <vector <double>> results;
    for (auto it : functions) {
        cerr << "Starting benchmark for " + it.second + " ...   ";
        try {
            auto x = Tester(it.first, VMAX, TMAX);
            results.push_back(x);
            cerr << "Done" << endl;
        } catch (...) {
            results.emplace_back();
        }

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

int main(int argv, char ** args)
{
    Benchmark(10000000, 2);
    return 0;

    auto sleep = [](int ml) {
        this_thread::sleep_for(chrono::milliseconds(ml));
    };


    auto message = [&](string s, int t) {
        cout << s << ' ';
        cout.flush();
        for (int i = 0; i < 10; i++) {
            cout << '.';
            cout.flush();
            sleep(t);
        }
        cout << " done!\n" << endl;
    };

    if (argv > 1) {
        vector <string> vec;
        for (int i = 1; i < argv; i++)
            vec.push_back(args[i]);

        if (vec[0][0] == 'r' || vec[0][0] == 'R') {
            bool found = 0;
            for (auto i : functions)
                if (i.second == vec[1])
                    ExecTime(i.first, vec[2]), found = 1;
            
            if (!found)
                cout << "Unable to find requested function." << endl;
        }
        else
            cout << "Invalid command\n";
        return 0;
    }
        
    cout << "Welcome to this super awesome project!\n\
    Here you will see more sorting algorithms than what you ever wished for ... " << endl;
    sleep(500);
    cout << "Whether you like it or not ..." << endl;
    sleep(200);

    message("Loading stuff", 300);
    message("Loading other stuff", 400);
    message("Still loading some stuff", 500);
    message("Personalizing UI experience", 600);

    cout << "Searching for available sorting algorithms ... " << endl;
    for (auto i : functions) {
        sleep(1000);
        cout << "Found " << i.second << endl;
    }
    cout << "\n\n";

    cout << "Available commands:\n\
    1. Benchmark [Max Value] [Max Time (miliseconds)]\n\
    2. Run [Sorting Algorithm] [Input File]\n\
    3. Exit" << endl;

    while (true) {
        cout << " $ ";
        cout.flush();
        string op;
        cin >> op;

        if (op[0] == 'b' || op[0] == 'B') {
            int vmax, tmax;
            cin >> vmax >> tmax;
            Benchmark(vmax, tmax / 1000.);
        }
        else if (op[0] == 'r' || op[0] == 'R') {
            string algorithm, file;
            cin >> algorithm >> file;

            bool found = 0;
            for (auto i : functions)
                if (i.second == algorithm)
                    ExecTime(i.first, file), found = 1;
            
            if (!found)
                cout << "Unable to find requested function." << endl;
        }
        else
            return 0;
    }

    return 0;
}
