#include "DFA.hpp"
#include "NFA.hpp"
using namespace std;

const string DFA::EPSILON = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

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
    /// edges in reverse direction
    vector <vector <int>> rev_edges(Q);

    /// computes the reverse edges
    for (int i = 0; i < Q; i++)
        for (auto it : edges_[i])
            rev_edges[it.second].push_back(i);

    /// bfs for reachable from start nodes
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

int DFA::CountStates() const
{
    return edges_.size(); 
}

DFA DFA::Minimize() const
{
    int Q = edges_.size();
    int cnt_states = 0;
    int id_end_nodes = -1, not_end_nodes = -1;

    /// for each new state what initial states it contained
    map <int, vector <int>> states;
    /// the state a node belongs to
    vector <int> node_state(Q);

    /// initial states are divided in end nodes / not end nodes
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

    /// while there is at least one class for which a caracter of epsilon does not send all 
    /// nodes in the same class, I have to break it in half

    /// which state a node with an edge is going to (-1 if none)
    auto delta = [&](int nod, char c) {
        if (edges_[nod].find(c) == edges_[nod].end() || !reachable_[edges_[nod].at(c)])
            return -1;
        return node_state[edges_[nod].at(c)];
    };

    /// while there is a class to break I have to break it
    for (bool ok = 1; (ok ^= 1) == 0; ) {
        for (int st = 0; st < cnt_states; st++) {
            for (auto c : EPSILON) {
                /// vreau sa vad daca se splituieste cv

                /// in ce se duce fiecare nod
                map <int, vector <int>> tranz;

                /// duc fiecare nod in noul lui state
                /// (vreau sa vad daca apar cel putin doua clase in tranz)
                for (auto i : states[st])
                    tranz[delta(i, c)].push_back(i);

                if (tranz.size() > 1) {
                    /// se splituieste in >= 2 stari
                    /// trebuie sa setez ok=true ca sa nu ies din for-ul principal
                    ok = 1;

                    /// given spune daca am asignat sau nu deja id-ul 'st'
                    bool given = 0;
                    for (auto & i : tranz) {
                        /// where este id-ul noii componente
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
        /// imi aleg un element random din state care ar trebui
        /// sa fie identic cu toti ceilalti
        int x = states[i][0];
        if (end_nodes_.find(x) != end_nodes_.end())
            new_end_nodes.insert(i);
        
        /// adaug muchiile din x la alte state-uri
        for (auto tr : edges_[x])
            if (reachable_[tr.second])
                new_edges[i][tr.first] = node_state[tr.second];
    }

    /// returnez DFA-ul
    return DFA(new_edges, new_start_node, new_end_nodes);
}

DFA operator~(const DFA& dfa)
{
    /**
     * ca sa iau negatia adaug un nod (sink node)
     * in care vars toate muchiile din epsilon care nu exista
     * si inversez starile finale cu cele nefinale
     */

    DFA ans = dfa;
    ans.edges_.emplace_back();

    int q = ans.edges_.size();

    /// daca nu exista o muchie atunci o creeze si o duc in (q - 1)
    for (auto c : ans.EPSILON)
        for (int i = 0; i < q; i++)
            if (ans.edges_[i].find(c) == ans.edges_[i].end())
                ans.edges_[i][c] = q - 1;

    /// inversez nodurile finale cu cele nefinale
    for (int i = 0; i < q; i++) {
        if (ans.end_nodes_.find(i) != ans.end_nodes_.end())
            ans.end_nodes_.erase(i);
        else
            ans.end_nodes_.insert(i);
    }
    
    /// returnez noul DFA
    return DFA(ans.edges_, ans.start_node_, ans.end_nodes_);
}

DFA operator|(const DFA& a, const DFA& b)
{
    /**
     * ca sa calculez reuniunea a doua DFA-uri
     * creeze un NFA cu o sursa noua si o muchie
     * de lambda de la sursa noua la cele doua surse intiale
     */

    /// creez noile muchii
    int sz_a = a.edges_.size(), sz_b = b.edges_.size();
    vector <map <char, set <int>>> new_edges(sz_a + sz_b + 1);
    
    /// add edges of a - add 1 to all of the nodes
    for (int i = 0; i < sz_a; i++)
        for (auto e : a.edges_[i])
            new_edges[i + 1][e.first].insert(e.second + 1);

    /// add edges of b - add (sz_a + 1) to all nodes
    for (int i = 0; i < sz_b; i++)
        for (auto e : b.edges_[i])
            new_edges[i + sz_a + 1][e.first].insert(e.second + sz_a + 1);
    
    /// creez tranzitiile lambda din 0
    new_edges[0][0].insert(a.start_node_ + 1);
    new_edges[0][0].insert(b.start_node_ + sz_a + 1);

    int new_start_node = 0;
    set <int> new_end_nodes;
    
    /// adaug end_nodes-urile
    for (auto i : a.end_nodes_)
        new_end_nodes.insert(i + 1);
    for (auto i : b.end_nodes_)
        new_end_nodes.insert(i + sz_a + 1);

    /// creez NFA-ul
    NFA reuniune(new_edges, new_start_node, new_end_nodes);

    /// returnez cast-ul NFA-ului la DFA
    return static_cast <DFA> (reuniune);
}


DFA operator&(const DFA& a, const DFA& b)
{
    /// a & b = ~((~a) | (~b))
    return ~((~a) | (~b));
}

bool operator==(const DFA& a, const DFA& b)
{
    /**
     *  Costel a zis ca e suficient sa verifici ca (A & ~B) = (B & ~A) = 0
     * vreau sa vad daca starile din minim1 si minim2 sunt identice
     * pana la permutare. Nu stiu daca e corect dar pare ok-ish
     */
    
    /// automatele minimizate
    DFA x = a.Minimize(), y = b.Minimize();

    /// daca nu au acelasi numar de stari atunci clar nu sunt egale
    if (x.edges_.size() != y.edges_.size())
        return 0;

    /// corespondenta de la a la b respectiv de la b la a
    map <int, int> a_to_b, b_to_a;
    vector <int> bfs;

    /// creeaza corespondenta (va == vb)
    auto verify = [&](int va, int vb) {
        if (a_to_b.find(va) != a_to_b.end() && a_to_b[va] != vb)
            return false;
        if (b_to_a.find(vb) != b_to_a.end() && b_to_a[vb] != va)
            return false;
        if (a_to_b.find(va) == a_to_b.end())
            bfs.push_back(va);
        a_to_b[va] = vb;
        b_to_a[vb] = va;
        return true;
    };

    verify(x.start_node_, y.start_node_);

    /// trece prin toate starile din BFS si se asigura ca sunt egale
    for (int it = 0; it < (int)bfs.size(); it++) {
        int n1 = bfs[it];
        int n2 = a_to_b[n1];

        bool n1_is_end_node = (x.end_nodes_.find(n1) == x.end_nodes_.end());
        bool n2_is_end_node = (y.end_nodes_.find(n2) == y.end_nodes_.end());

        if (n1_is_end_node ^ n2_is_end_node)
            return 0;

        for (auto c : a.EPSILON) {
            int x_has_c = (x.edges_[n1].find(c) != x.edges_[n1].end());
            int y_has_c = (y.edges_[n2].find(c) != y.edges_[n2].end());
            if (x_has_c ^ y_has_c)
                return 0;
            if (x_has_c && !verify(x.edges_[n1][c], y.edges_[n2][c]))
                return 0;
        }
    }

    return true;
}

bool operator!= (const DFA & a, const DFA & b)
{
    /// a != b <=> !(a = b)     DUH!
    return !(a == b);
}

istream & operator>> (istream & in, DFA & dfa)
{
    try {
        int Q, szTranz;
        in >> Q >> szTranz;

        if (Q < 1 || szTranz < 0)
            throw runtime_error("Invalid input");

        dfa.edges_ = vector <map <char, int>> (Q);
        
        while (szTranz--) {
            int X, Y;
            char c;
            in >> X >> Y >> c;

            if (min(X, Y) < 0 || max(X, Y) >= Q)
                throw runtime_error("Invalid input");

            dfa.edges_[X][c] = Y;
        }

        in >> dfa.start_node_;

        if (dfa.start_node_ < 0 || dfa.start_node_ >= Q)
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


ostream & operator<< (ostream & out, const DFA & dfa)
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