#include <bits/stdc++.h>
#include "DFA.hpp"
using namespace std;

mt19937 rnd(0); 

void tester(DFA x, int sigma)
{
    DFA minim = x.Minimize();
    
    for (int _ = 0; _ < 10000; _++) {
        string s;
        int l = rnd() % 8;
        for (int i = 0; i < l; i++)
            s += 'a' + rnd() % sigma;
        
        if (x.IsAccepted(s) ^ minim.IsAccepted(s)) {
            cerr << "Error for " << s << '\n';
            cerr << "X.IsAccepted(" << s << ") = " << x.IsAccepted(s) << "\nBut minim.IsAccepted(" << s << ") = ";
            cerr << minim.IsAccepted(s) << "!!\n";
            cerr << "Initial DFA: " << x << '\n' << "Minimized DFA: " << minim << '\n';
            exit(0);
        }
    }
    static int cnt = 0;
    cerr << "Ok for " << cnt++ << '\n';
}

DFA make_random(int sigma)
{
    int start_node = 0;
    int l = rnd() % 15 + 1;
    set <int> end_nodes = { (int)(rnd() % l), (int)(rnd() % l) };
    vector <map <char, int>> edges(l);
    for (int i = 0; i < 2 * l * l; i++) {
        char c = rnd() % sigma + 'a';
        edges[rnd() % l][c] = rnd() % l;
    }

    return DFA(edges, start_node, end_nodes);
}

int main()
{

    while (1) {
        DFA r = make_random(4);
        //cout << r << '\n';
        tester(r, 4);
    }

    ifstream in("input.txt");

    DFA a;
    in >> a;

    cout << a;

    cout << "\n\nMinimized DFA:\n";
    
    DFA minim = a.Minimize();

    cout << minim << '\n';
    
    return 0; 
}