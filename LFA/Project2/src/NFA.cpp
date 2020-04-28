#include <bits/stdc++.h>
#include "NFA.hpp"
using namespace std;

const string NFA::EPSILON = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";


NFA::NFA(vector <map <char, set <int>>> edges, int start_node, set <int> end_nodes):
    edges_(edges), start_node_(start_node), end_nodes_(end_nodes) {

}

NFA::NFA() { }
    
NFA::operator DFA()
{
    /// first, need to get rid of lambda-transitions
    int N = edges_.size();

    /// if NFA is empty there is nothing to do
    if (N == 0)
        return DFA();

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

    /// creating echivalent DFA

    /// mapping from the subsets of nodes of the NFA to nodes of the DFA
    map <set <int>, int> norm_states;
    /// transitions between the new states of the DFA
    vector <map <char, int>> new_tranz;
    /// states I need to process in a BFS-like fasion
    vector <set <int>> to_process;
    /// new start node of the DFA
    int new_start_node = 0;
    /// new end nodes of the DFA
    set <int> new_end_nodes;

    /** 
     * returns the state asociated to a subset of the nodes of the NFA
     * If the state does not exist it creates it
     */
    auto GetNorm = [&](const set <int> & v) {
        if (norm_states.find(v) == norm_states.end()) {
            int x = norm_states.size();
            norm_states[v] = x;
            new_tranz.emplace_back();
            to_process.push_back(v);
        }
        return norm_states[v];
    };

    /// creates the initial state of the DFA
    GetNorm({ start_node_ });

    /// iterates the created states in the DFA
    for (int id = 0; id < (int)to_process.size(); id++) {
        set <int> st = to_process[id];
        assert(GetNorm(st) == id);

        /// if at least one of the nodes in the state is an end note
        /// then the echivalent state of the DFA is an end state
        for (auto i : st)
            if (end_nodes_.find(i) != end_nodes_.end())
                new_end_nodes.insert(id);
        
        /// tries all possible characters to go to new states
        for (char c : EPSILON) {
            set <int> new_state;
            for (auto i : st)
                for (auto j : edges_[i][c])
                    new_state.insert(j);

            /// creates the new edge in the DFA
            if (!new_state.empty())
                new_tranz[id][c] = GetNorm(new_state);
        }
    }

    /// returns the new DFA
    return DFA(new_tranz, new_start_node, new_end_nodes);
}


istream & operator>> (istream & in, NFA & nfa)
{
    try {
        int Q, szTranz;
        in >> Q >> szTranz;

        if (Q < 1 || szTranz < 0)
            throw runtime_error("Invalid input");

        nfa.edges_ = vector <map <char, set <int>>> (Q);
        
        while (szTranz--) {
            int X, Y;
            char c;
            in >> X >> Y >> c;

            if (min(X, Y) < 0 || max(X, Y) >= Q)
                throw runtime_error("Invalid input");

            nfa.edges_[X][c].insert(Y);
        }

        in >> nfa.start_node_;
        
        if (nfa.start_node_ < 0 || nfa.start_node_ >= Q)
            throw runtime_error("Invalid input");

        int szF;
        in >> szF;

        if (szF < 0)
            throw runtime_error("Invalid input");

        while (szF--) {
            int X;
            in >> X;
            if (X < 0 || X >= Q)
                throw runtime_error("Invalid input");

            nfa.end_nodes_.insert(X);
        }
    }
    catch (...) {
        cerr << "There was a problem in reading the NFA...\n";
        cerr << "Maybe the input is not valid?" << endl;
        nfa = NFA();
    }

    return in;
}


ostream & operator<< (ostream & out, const NFA & nfa)
{
    out << "NFA at memory " << &nfa << ":\n";
    out << "Number of states: " << nfa.edges_.size() << endl;
    out << "Starting state: " << nfa.start_node_ << endl;
    out << "Ending states: " << "{ ";
    for (auto i : nfa.end_nodes_)
        out << i << ' ';
    out << "}\n";
    
    for (int i = 0; i < (int)nfa.edges_.size(); i++) {
        out << "Edges from " << i << ": ";
        string sep = "";
        for (auto it : nfa.edges_[i]) {
            for (auto i : it.second) {
                out << sep << "{ " << it.first << ", " << i << " }";
                sep = ", ";
            }
        }
        out << '\n';
    }
    return out;
}
