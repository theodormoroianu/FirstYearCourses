#include "regram.hpp"
#include "NFA.hpp"

#include <bits/stdc++.h>
using namespace std;

Regram::Regram() { }

Regram::Regram(const string & initial_state, const map <string,
    vector <pair <char, string>>> & gram) : regram_(gram), initial_state_(initial_state) { }

Regram::Regram(const DFA & dfa)
{
    FromDfa(dfa);
}

DFA Regram::ToDfa() const
{
    vector <map <char, set <int>>> edges;
    map <string, int> nrm;

    auto get_id = [&](string s) -> int {
        if (nrm.find(s) == nrm.end()) {
            int x = nrm.size();
            nrm[s] = x;
            edges.emplace_back();
        }
        return nrm[s];
    };

    int start_node = get_id(initial_state_);
    set <int> end_nodes = { get_id("") };

    for (auto & i : regram_) {
        int id = get_id(i.first);
        for (auto & tranz : i.second) {
            edges[id][tranz.first].insert(get_id(tranz.second));        
        }
    }

    NFA nfa(edges, start_node, end_nodes);
    DFA dfa = static_cast <DFA> (nfa);

    return dfa;
}

void Regram::FromDfa(const DFA & dfa)
{
    vector <string> to_state(dfa.edges_.size());
    for (int i = 0; i < (int)to_state.size(); i++) {
        string ans;
        int id = i;
        do {
            ans.push_back('A' + id % 26);
            id /= 26;
        } while (id);
        to_state[i] = ans;
    }

    initial_state_ = to_state[dfa.start_node_];
    regram_.clear();

    for (int i = 0; i < (int)dfa.edges_.size(); i++) {
        for (auto op : dfa.edges_[i])
            regram_[to_state[i]].push_back({ op.first, to_state[op.second] });
        if (dfa.end_nodes_.find(i) != dfa.end_nodes_.end())
            regram_[to_state[i]].push_back({ 0, "" });
    }
}

map <string,
    vector <pair <char, string>>> Regram::GetContent() const
{
    return regram_;
}

istream & operator>> (istream & in, Regram & reg)
{
    /**
     * Input is given as:
     * 1. Number of productions
     * 2. Productions given as S [' ' / ':' / '->'] aG|fG ...
     * 3. Epsilon is noted with '@' 
     * 4. Initial state
     * 5. States are ALWAYS in capital letters and
     *    characters are ALWAYS lower letters
     */

    try {

        auto parse = [](string s) -> pair<char, string> {
            if (s.empty())
                throw exception();
            if (('a' <= s[0] && s[0] <= 'z') || s[0] == '@')
                return { (s[0] == '@' ? 0 : s[0]), s.substr(1) };
            return { 0, s };
        };

        int nrprod;
        in >> nrprod;
        in.ignore();
        
        reg = Regram();
        while (nrprod--) {
            string s;
            getline(in, s);
            s.push_back('|');
            string beg;
            int poz = 0;

            while ('A' <= s[poz] && s[poz] <= 'Z')
                beg += s[poz++];

            assert(!beg.empty());
            string last;

            for ( ; poz < (int)s.size(); poz++) {
                if (('a' <= s[poz] && s[poz] <= 'z') ||
                  ('A' <= s[poz] && s[poz] <= 'Z') || s[poz] == '@') {
                      last += s[poz];
                }
                else if (!last.empty()) {
                    reg.regram_[beg].push_back(parse(last));
                    last = "";
                }
            }
        }

        in >> reg.initial_state_;
    }
    catch (...) {
        throw runtime_error("Invalid input!");
        reg = Regram();
    }

    return in;
}

ostream & operator<< (ostream & out, const Regram & reg)
{
    out << "Regular grammar at location <" << &reg << ">:\n";
    out << "Number of symbols: " << reg.regram_.size() << '\n';
    out << "Productions:\n";
    for (auto i : reg.regram_) {
        static int cnt = 0;
        out << ' ' << ++cnt << ": " + i.first + " -> ";
        string o = "";
        for (auto p : i.second) {
            out << o << (p.first ? p.first : '@') << p.second;
            o = " | ";
        }
        out << '\n';
    }

    return out;
}