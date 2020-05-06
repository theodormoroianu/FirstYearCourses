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

/// pentru labul 5 la LFA
void Ex1Lab()
{
    string s;
    cin >> s;
    int N = s.size();

    vector <map <char, set <int>>> edges;
    map <pair <string, int>, int> nrm;
    vector <pair <string, int>> bfs;
    set <int> end_nodes;

    auto get_id = [&](string s, int id) -> int {
        if (nrm.find({ s, id }) == nrm.end()) {
            int x = nrm.size();
            nrm[{ s, id }] = x;
            edges.emplace_back();
            bfs.push_back({ s, id });
        }
        return nrm[{ s, id }];
    };

    get_id(s, 0);

    for (int it = 0; it < (int)bfs.size(); it++) {
        string act;
        int l;
        tie(act, l) = bfs[it];
        int id = get_id(act, l);

        if (l != (int)act.size()) {
            edges[id][act[l]].insert(get_id(act, l + 1));
            continue;
        }
        end_nodes.insert(id);
        for (int suff = 1; suff <= (int)act.size(); suff++) {
            string new_str = act + act.substr(act.size() - suff);
            new_str = new_str.substr(new_str.size() - N);
            int new_offset = new_str.size() - suff;
            edges[id][new_str[new_offset]].insert(get_id(new_str, new_offset + 1));
        }
    }

    NFA nfa(edges, 0, end_nodes);

    DFA dfa = static_cast<DFA>(nfa);
    dfa = dfa.Minimize();

    cout << dfa << '\n';

    while (true) {
        string s;
        cin >> s;
        cout << dfa.IsAccepted(s) << '\n';
    }
}

int main()
{
    // Ex1Lab();
    // return 0;

    UnitTests();

    ConvertNFAtoDfA();
    
    return 0; 
}