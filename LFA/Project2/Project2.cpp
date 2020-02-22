#include <bits/stdc++.h>
#include "DFA.hpp"
using namespace std;

int main()
{
    ifstream in("input.txt");

    DFA a;
    in >> a;
    
    cout << a;

    cout << "\n\nMinimized DFA:\n";
    
    DFA minim = a.Minimize();

    cout << minim << '\n';
    
    return 0; 
}