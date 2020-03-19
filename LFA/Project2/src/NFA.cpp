#include <bits/stdc++.h>
#include "NFA.hpp"
using namespace std;

const string NFA::EPSILON = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

NFA::NFA(vector <map <char, set <int>>> edges, int start_node, set <int> end_nodes):
    edges_(edges), start_node_(start_node), end_nodes_(end_nodes) {

}
    
NFA::operator DFA()
{
    // first, need to get rid of lambda-stransitions
    int N = edges_.size();
    for (bool modif = 1; (modif ^= 1) == 0; ) {

        for (int node = 0; node < N; node++) {
            for (auto i : edges_[node][0]) {
                /// propagate the ending states
                if (end_nodes_.find(node) == end_nodes_.end() && end_nodes_.find(i) != end_nodes_.end()) {
                    end_nodes_.insert(node);
                    modif = 1;
                }

                /// all the neigours of i should be mine too
                for (auto & tranz : edges_[i]) {
                    for (auto & j : tranz.second) {
                        if (edges_[node][tranz.first].find(j) == edges_[node][tranz.first].end()) {
                            modif = 1;
                            edges_[node][tranz.first].insert(j);
                        }
                    }
                }
            }
        }
    }

    map <set <int>, int> norm_states;
    vector <map <char, int>> new_tranz;
    vector <set <int>> to_process;
    int new_start_node = 0;
    set <int> new_end_nodes;

    auto GetNorm = [&](const set <int> & v) {
        if (norm_states.find(v) == norm_states.end()) {
            int x = norm_states.size();
            norm_states[v] = x;
            new_tranz.emplace_back();
            to_process.push_back(v);
        }
        return norm_states[v];
    };

    GetNorm({ start_node_ });

    for (int id = 0; id < (int)to_process.size(); id++) {
        set <int> st = to_process[id];
        
        for (auto i : st)
            if (end_nodes_.find(i) != end_nodes_.end())
                new_end_nodes.insert(id);
        
        for (char c : EPSILON) {
            set <int> new_state;
            for (auto i : st)
                for (auto j : edges_[i][c])
                    new_state.insert(j);
            if (!new_state.empty())
                new_tranz[id][c] = GetNorm(new_state);
        }
    }

    return DFA(new_tranz, new_start_node, new_end_nodes);
}