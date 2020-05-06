#include <bits/stdc++.h>
using namespace std;

#include "DFA.hpp"
#include "NFA.hpp"
#include "regex.hpp"
#include "regram.hpp"
#include "unit_tests.hpp"

void ConvertNFAtoDFA()
{
    ifstream in("input.txt");
    NFA x;
    in >> x;
    DFA dfa = static_cast<DFA>(x);
    dfa = dfa.Minimize();

    ofstream out("output.txt");
    out << dfa << '\n';
}

void ConvertRegexToDFA()
{
    ifstream in("input.txt");
    Regex x;
    in >> x;
    DFA dfa = x.ToDfa();
    dfa = dfa.Minimize();

    ofstream out("output.txt");
    out << dfa << '\n';
}

void ConvertDFAToRegex()
{
    ifstream in("input.txt");
    DFA d;
    in >> d;
    Regex x(d);
    ofstream out("output.txt");
    out << x << '\n';
}

void ConvertRegramToDFA()
{
    ifstream in("input.txt");
    Regram x;
    in >> x;
    DFA dfa = x.ToDfa();
    dfa = dfa.Minimize();

    ofstream out("output.txt");
    out << dfa << '\n';
}

void ConvertDFAToRegram()
{
    ifstream in("input.txt");
    DFA d;
    in >> d;
    Regram x(d);
    ofstream out("output.txt");
    out << x << '\n';
}

int main()
{
    cout << "Welcome!\nAll operations are made from `input.txt` to `output.txt`\n";
    cout << "Available commands:\n";
    cout << "1. Convert NFA to DFA\n";
    cout << "2. Convert Regex to DFA\n";
    cout << "3. Convert DFA to Regex\n";
    cout << "4. Convert regular grammar to DFA\n";
    cout << "5. Convert DFA to regular grammar\n";
    cout << "6. Exit\n";

    while (1) {
        cout << " $ ";
        int x;
        cin >> x;
        if (x == 1)
            ConvertNFAtoDFA();
        else if (x == 2)
            ConvertRegexToDFA();
        else if (x == 3)
            ConvertDFAToRegex();
        else if (x == 4)
            ConvertRegramToDFA();
        else if (x == 5)
            ConvertDFAToRegram();
        else
            break;
        cout << "Done!\n";
    }
    return 0; 
}