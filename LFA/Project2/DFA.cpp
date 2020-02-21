#include "DFA.hpp"
using namespace std;

void Assert(bool x)
{
    if (!x)
        throw exception();
}

void DFA::compute_reachability() 
{
    int Q = edges.size();
    vector <bool> reachable_from_start(Q, 0);
    vector <bool> reachable_from_end(Q, 0);
    vector <vector <int>> rev_edges(Q);

    for (int i = 0; i < Q; i++)
        for (auto it : edges[i])
            rev_edges[it.second].push_back(i);

    vector <int> bfs = { start_node };
    reachable_from_start[start_node] = 1;

    // compute reachable_from_start (aka if i can get there from start)
    for (int it = 0; it < (int)bfs.size(); it++) {
        int node = bfs[it];
        for (auto tranz : edges[node]) {
            if (!reachable_from_start[tranz.second]) {
                reachable_from_start[tranz.second] = 1;
                bfs.push_back(tranz.second);
            }
        }
    }

    // compute reachable_from_end (aka if i can get to an end_node)
    bfs.clear();
    for (auto i : end_nodes) {
        bfs.push_back(i);
        reachable_from_end[i] = 1;
    }

    for (int it = 0; it < (int)bfs.size(); it++) {
        int node = bfs[it];
        for (auto tranz : rev_edges[node]) {
            if (!reachable_from_end[tranz]) {
                reachable_from_end[tranz] = 1;
                bfs.push_back(tranz);
            }
        }
    }

    reachable = vector <bool> (Q);
    for (int i = 0; i < Q; i++)
        reachable[i] = (reachable_from_end[i] & reachable_from_start[i]);
}

DFA::DFA() : start_node(-1) { }


DFA::DFA(vector <map <char, int>> edges, int start_node, set <int> end_nodes) :
    edges(edges), start_node(start_node), end_nodes(end_nodes)
{
    compute_reachability();
}

bool DFA::IsAccepted(const string & s) const
{
    int state = start_node;
    for (auto i : s) {
        if (edges[state].find(i) == edges[state].end())
            return 0;
        state = edges[state].at(i);
    }
    return end_nodes.find(state) != end_nodes.end();
}

DFA DFA::Minimize() const
{
    int Q = edges.size();
    map <int, vector <int>> states;
    vector <int> node_state(Q);

    for (int i = 0; i < Q; i++) {
        if (!reachable[i])
            continue;
        if (end_nodes.find(i) != end_nodes.end()) {
            node_state[i] = 1;
            states[1].push_back(i);
        }
        else {
            node_state[i] = 0;
            states[0].push_back(i);
        }
    }

    // while there is at least one class for which a caracter of epsilon does not send all 
    // nodes in the same class, I have to break it in half

    int cnt_states = 2;
    auto delta = [&](int nod, char c) {
        if (edges[nod].find(c) == edges[nod].end())
            return -1;
        return node_state[edges[nod].at(c)];
    };

    for (bool ok = 1; (ok ^= 1) == 0; ) {
        for (int st = 0; st < cnt_states; st++) {
            for (auto c : EPSILON) {
                /// vreau sa vad daca se splituieste cv

                map <int, vector <int>> tranz;

                for (auto i : states[st])
                    tranz[delta(i, c)].push_back(i);

                if (tranz.size() > 1) {
                    /// se splituieste in >= 2 stari
                    ok = 1;

                    bool given = 0;
                    for (auto & i : tranz) {
                        int where = (given ? cnt_states++ : st);
                        given = 1;
                        states[where] = i.second;
                    }
                }
            }
        }
    }

    /// construction of new DFA
    vector <map <char, int>> new_edges(cnt_states);
    /// There is a problem when there is no non-ending node for eq, as there won't be
    // any node with state=0
    TODO   
}

istream & operator>> (istream & in, DFA & dfa)
{
    try {
        int Q, szTranz;
        in >> Q >> szTranz;

        Assert(Q >= 1);
        Assert(szTranz >= 0);

        dfa.edges = vector <map <char, int>> (Q);
        
        while (szTranz--) {
            int X, Y;
            char c;
            in >> X >> Y >> c;

            Assert(min(X, Y) >= 0 && max(X, Y) < Q);
            Assert(dfa.edges[X].find(c) == dfa.edges[X].end());
            dfa.edges[X][c] = Y;
        }

        in >> dfa.start_node;
        Assert(dfa.start_node >= 0 && dfa.start_node < Q);

        int szF;
        in >> szF;
        Assert(szF >= 0);

        while (szF--) {
            int X;
            in >> X;
            Assert(X >= 0 && X < Q && dfa.end_nodes.find(X) == dfa.end_nodes.end());
            dfa.end_nodes.insert(X);
        }
    }
    catch (...) {
        cerr << "There was a problem in reading the DFA...\n";
        cerr << "Maybe the input is not valid?" << endl;
        dfa = DFA();
    }

    dfa.compute_reachability();

    return in;
}


ostream & operator<< (ostream & out, DFA & dfa)
{
    out << "DFA at memory " << &dfa << ":\n";
    out << "Number of states: " << dfa.edges.size() << endl;
    out << "Starting state: " << dfa.start_node << endl;
    out << "Ending states: " << "{ ";
    for (auto i : dfa.end_nodes)
        out << i << ' ';
    out << "}\n";
    
    out << "Reachable nodes: " << " { ";
    for (int i = 0; i < (int)dfa.edges.size(); i++)
        if (dfa.reachable[i])
            out << i << ' ';
    out << "}\n";
    for (int i = 0; i < (int)dfa.edges.size(); i++) {
        out << "Edges from " << i << ": ";
        string sep = "";
        for (auto it : dfa.edges[i]) {
            out << sep << "{ " << it.first << ", " << it.second << " }";
            sep = ", ";
        }
        out << '\n';
    }
    return out;
}