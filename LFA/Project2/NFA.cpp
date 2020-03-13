#include <bits/stdc++.h>
#include "NFA.hpp"
using namespace std;


NFA::NFA(vector <map <char, vector <int>>> edges, int start_node, set <int> end_nodes):
    edges_(edges), start_node_(start_node), end_nodes_(end_nodes) {

}
    
NFA::operator DFA()
{
    map <vector <int>, int> norm_states;
    auto GetNorm = [&](vector <int> & v) {
        if (norm_states.find(v) != norm_states.end()) {
            int x = norm_states.size();
            norm_states[v] = x;
        }
        return norm_states[v];
    };

    return DFA();
    // TODO
}