#include <bits/stdc++.h>
#include "DFA.hpp"
#include "NFA.hpp"
#include "unit_tests.hpp"
using namespace std;

void ConvertNFAtoDfA()
{
    ifstream in("input.txt");
    NFA x;
    in >> x;
    DFA dfa = static_cast<DFA>(x);
    dfa = dfa.Minimize();

    ofstream out("output.txt");
    out << dfa << '\n';
}

int main()
{
    UnitTests();

    // ConvertNFAtoDfA();
    
    return 0; 
}