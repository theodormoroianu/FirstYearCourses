#include "regex.hpp"
#include "NFA.hpp"

using namespace std;

Regex::Regex() { }

Regex::Regex(const std::string & s) : regex_(s) { }

Regex::Regex(const DFA & dfa)
{
    FromDfa(dfa);
}

DFA Regex::ToDfa() const
{
    /**
     * Transforms a regex into a dfa
     * with a queue-like approach by combining
     * adjacent elements
     */
    vector <map <char, set <int>>> edges;

    auto AddState = [&]() -> int {
        edges.emplace_back();
        return edges.size() - 1;
    };

    /// -1 if not node
    vector <tuple <char, int, int>> q;

    for (auto c : regex_) {
        if (c == '(') {
            q.emplace_back('(', -1, -1);
            continue;
        }
        else if (c == '|') {
            if (q.empty() || get<1>(q.back()) == -1)
                throw runtime_error("Invalid regex!");
            q.push_back(make_tuple('|', -1, -1));
            continue;
        }
        else if (c == '*') {
            if (q.empty() || get<1>(q.back()) == -1)
                throw runtime_error("Invalid regex!");
            /// add a loop with lambda edge
            int node = AddState();
            edges[node][0].insert(get<1>(q.back()));
            edges[get<2>(q.back())][0].insert(node);
            q.back() = make_tuple(0, node, node);
            continue;
        }

        int from, to;
        
        if (c == ')') {
            if (q.size() < 2 || get<0>(q[q.size() - 2]) != '(')
                throw runtime_error("Invalid regex!");
            q.erase(q.end() - 2);
            from = get<1>(q.back()), to = get<2>(q.back());
            q.pop_back();
        }
        else {
            /// main case, new caracter appears
            from = AddState(), to = AddState();
            edges[from][c == '@' ? 0 : c].insert(to);
        }

        if (!q.empty() && get<1>(q.back()) != -1) {
            /// combine with concatenation
            edges[get<2>(q.back())][0].insert(from);
            get<2>(q.back()) = to;
            continue;
        }

        if (!q.empty() && get<0>(q.back()) == '|') {
            /// or of two nodes
            int new_to = AddState(), new_from = AddState();
            q.pop_back();
            edges[new_from][0].insert(from);
            edges[new_from][0].insert(get<1>(q.back()));
            edges[to][0].insert(new_to);
            edges[get<2>(q.back())][0].insert(new_to);
            q.back() = make_tuple(0, new_from, new_to);
            continue;
        }

        q.emplace_back(0, from, to);
    }

    if (q.size() != 1 || get<1>(q[0]) == -1)
        throw runtime_error("Invalid regex!");
    
    NFA nfa(edges, get<1>(q[0]), { get<2>(q[0]) });
    return static_cast <DFA> (nfa);
}

void Regex::FromDfa(const DFA & dfa)
{
    /**
     * First I create the new automaton,
     * in which I added a dummy source and destination
     * then I remove one by one the nodes and make
     * some voodo magic and it works
     */
    vector <map <int, string>> edges(dfa.edges_.size() + 2);
    vector <set <int>> rev_edges(dfa.edges_.size() + 2);

    int start_node = dfa.edges_.size();
    int end_node = start_node + 1;

    edges[start_node][dfa.start_node_] = "";
    rev_edges[dfa.start_node_].insert(start_node);

    for (auto i : dfa.end_nodes_) {
        edges[i][end_node] = "";
        rev_edges[end_node].insert(i);
    }

    /// computes OR of two strings
    auto MakeOr = [](string a, string b) {
        if (a.empty())
            a = "@";
        if (b.empty())
            b = "@";
        return "(" + a + "|" + b + ")";
    };

    for (int i = 0; i < (int)dfa.edges_.size(); i++) {
        for (auto j : dfa.edges_[i]) {
            if (edges[i].find(j.second) != edges[i].end())
                edges[i][j.second] = MakeOr(string(1, j.first), edges[i][j.second]);
            else
                edges[i][j.second] = string(1, j.first);
            rev_edges[j.second].insert(i);
        }
    }


    auto RemoveNode = [&](int id) {
        string inside = "";
        if (edges[id].find(id) != edges[id].end())
            inside = edges[id][id];
        if (!inside.empty())
            inside = "(" + inside + "*)";

        for (auto from : rev_edges[id]) {
            if (from == id)
                continue;
            for (auto to : edges[id]) {
                if (to.first == id)
                    continue; /// no need to process it

                string act = "(" + edges[from][id] + inside + to.second + ")";
                if (act.size() <= 3)
                    act = (act.size() == 2 ? "@" : act.substr(1, 1));

                if (edges[from].find(to.first) == edges[from].end())
                    edges[from][to.first] = act;
                else
                    edges[from][to.first] = MakeOr(edges[from][to.first], act);
                
                rev_edges[to.first].insert(from);
            }
            edges[from].erase(id);
        }
        for (auto to : edges[id])
            rev_edges[to.first].erase(id);
    };

    for (int i = 0; i < (int)dfa.edges_.size(); i++)
        RemoveNode(i);

    regex_ = edges[start_node][end_node];
}

string Regex::GetContent() const
{
    return regex_;
}


istream & operator>> (istream & in, Regex & reg)
{
    in >> reg.regex_;
    return in;
}

ostream & operator<< (ostream & out, const Regex & reg)
{
    out << reg.regex_;
    return out;
}
