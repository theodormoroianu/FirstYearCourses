#include "DFA.hpp"
#include "NFA.hpp"
using namespace std;

const string DFA::EPSILON = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

namespace {
    void Assert(bool x)
    {
        if (!x)
            throw exception();
    }
}

void DFA::compute_reachability() 
{
    // if there are no nodes (I have an empty DFA)
    // I add a virtual node with no edges and no ending_states
    if (edges_.empty()) {
        edges_.emplace_back();
        start_node_ = 0;
    }

    int Q = edges_.size();
    vector <bool> reachable_from_start(Q, 0);
    vector <bool> reachable_from_end(Q, 0);
    vector <vector <int>> rev_edges(Q);

    for (int i = 0; i < Q; i++)
        for (auto it : edges_[i])
            rev_edges[it.second].push_back(i);

    vector <int> bfs = { start_node_ };
    reachable_from_start[start_node_] = 1;

    // compute reachable_from_start (aka if i can get there from start)
    for (int it = 0; it < (int)bfs.size(); it++) {
        int node = bfs[it];
        for (auto tranz : edges_[node]) {
            if (!reachable_from_start[tranz.second]) {
                reachable_from_start[tranz.second] = 1;
                bfs.push_back(tranz.second);
            }
        }
    }

    // compute reachable_from_end (aka if i can get to an end_node)
    bfs.clear();
    for (auto i : end_nodes_) {
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

    // a node is reachable if it sees both starting and ending nodes
    reachable_ = vector <bool> (Q);
    for (int i = 0; i < Q; i++)
        reachable_[i] = (reachable_from_end[i] & reachable_from_start[i]);
}

DFA::DFA()
{
    compute_reachability();
}


DFA::DFA(vector <map <char, int>> edges, int start_node, set <int> end_nodes) :
    edges_(edges), start_node_(start_node), end_nodes_(end_nodes)
{
    compute_reachability();
}

bool DFA::IsAccepted(const string & s) const
{
    int state = start_node_;
    for (auto i : s) {
        if (edges_[state].find(i) == edges_[state].end())
            return 0;
        state = edges_[state].at(i);
    }
    return end_nodes_.find(state) != end_nodes_.end();
}

DFA DFA::Minimize() const
{
    int Q = edges_.size();
    int cnt_states = 0;
    int id_end_nodes = -1, not_end_nodes = -1;

    map <int, vector <int>> states;
    vector <int> node_state(Q);

    for (int i = 0; i < Q; i++) {
        if (!reachable_[i])
            continue;
        if (end_nodes_.find(i) != end_nodes_.end()) {
            if (id_end_nodes == -1)
                id_end_nodes = cnt_states++;
            node_state[i] = id_end_nodes;
            states[id_end_nodes].push_back(i);
        }
        else {
            if (not_end_nodes == -1)
                not_end_nodes = cnt_states++;
            node_state[i] = not_end_nodes;
            states[not_end_nodes].push_back(i);
        }
    }

    // while there is at least one class for which a caracter of epsilon does not send all 
    // nodes in the same class, I have to break it in half

    // which state a node with an edge is going to (-1 if none)
    auto delta = [&](int nod, char c) {
        if (edges_[nod].find(c) == edges_[nod].end() || !reachable_[edges_[nod].at(c)])
            return -1;
        return node_state[edges_[nod].at(c)];
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
                        for (auto x : i.second)
                            node_state[x] = where;
                    }
                }
            }
        }
    }

    /// construction of new DFA
    vector <map <char, int>> new_edges(cnt_states);
    set <int> new_end_nodes;
    int new_start_node = node_state[start_node_];

    for (int i = 0; i < cnt_states; i++) {
        int x = states[i][0];
        if (end_nodes_.find(x) != end_nodes_.end())
            new_end_nodes.insert(i);
        for (auto tr : edges_[x])
            if (reachable_[tr.second])
                new_edges[i][tr.first] = node_state[tr.second];
    }

    return DFA(new_edges, new_start_node, new_end_nodes);
}

DFA operator~(const DFA & dfa)
{
    DFA ans = dfa;
    int q = ans.edges_.size();
    for (int i = 0; i < q; i++) {
        if (ans.end_nodes_.find(i) != ans.end_nodes_.end())
            ans.end_nodes_.erase(i);
        else
            ans.end_nodes_.insert(i);
    }
    return ans;
}

DFA operator|(const DFA & a, const DFA & b)
{
    int sz_a = a.edges_.size(), sz_b = b.edges_.size();
    vector <map <char, set <int>>> new_edges(sz_a + sz_b + 1);
    
    /// add edges of a
    for (int i = 0; i < sz_a; i++)
        for (auto e : a.edges_[i])
            new_edges[i + 1][e.first].insert(e.second + 1);

    for (int i = 0; i < sz_a; i++)
        for (auto e : a.edges_[i])
            new_edges[i + sz_a + 1][e.first].insert(e.second + sz_a + 1);
    
    new_edges[0][0].insert(1);
    new_edges[0][0].insert(sz_a + 1);

    int new_start_node = 0;
    set <int> new_end_nodes;
    
    for (auto i : a.end_nodes_)
        new_end_nodes.insert(i);
    for (auto i : b.end_nodes_)
        new_end_nodes.insert(i);

    NFA reuniune(new_edges, new_start_node, new_end_nodes);

    return static_cast <DFA> (reuniune);
}


DFA operator&(const DFA & a, const DFA & b)
{
    /// a & b = ~((~a) | (~b))
    return ~((~a) | (~b));
}

istream & operator>> (istream & in, DFA & dfa)
{
    try {
        int Q, szTranz;
        in >> Q >> szTranz;

        Assert(Q >= 1);
        Assert(szTranz >= 0);

        dfa.edges_ = vector <map <char, int>> (Q);
        
        while (szTranz--) {
            int X, Y;
            char c;
            in >> X >> Y >> c;

            Assert(min(X, Y) >= 0 && max(X, Y) < Q);
            Assert(dfa.edges_[X].find(c) == dfa.edges_[X].end());
            dfa.edges_[X][c] = Y;
        }

        in >> dfa.start_node_;
        Assert(dfa.start_node_ >= 0 && dfa.start_node_ < Q);

        int szF;
        in >> szF;
        Assert(szF >= 0);

        while (szF--) {
            int X;
            in >> X;
            Assert(X >= 0 && X < Q && dfa.end_nodes_.find(X) == dfa.end_nodes_.end());
            dfa.end_nodes_.insert(X);
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
    out << "Number of states: " << dfa.edges_.size() << endl;
    out << "Starting state: " << dfa.start_node_ << endl;
    out << "Ending states: " << "{ ";
    for (auto i : dfa.end_nodes_)
        out << i << ' ';
    out << "}\n";
    
    out << "Reachable nodes: " << " { ";
    for (int i = 0; i < (int)dfa.edges_.size(); i++)
        if (dfa.reachable_[i])
            out << i << ' ';
    out << "}\n";
    for (int i = 0; i < (int)dfa.edges_.size(); i++) {
        out << "Edges from " << i << ": ";
        string sep = "";
        for (auto it : dfa.edges_[i]) {
            out << sep << "{ " << it.first << ", " << it.second << " }";
            sep = ", ";
        }
        out << '\n';
    }
    return out;
}