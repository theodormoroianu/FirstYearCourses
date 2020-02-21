#include <bits/stdc++.h>
using namespace std;

class Automat {
    vector <map <char, vector <int>>> tranzitii;
    vector <vector <int>> backward;
    vector <int> accesibil;
    set <int> final_states, initial_states;

    /// makes the curent state given by actual through the edge 'edge'
    set <int> step(set <int> actual, char edge) {
        set <int> after_step;
        for (auto i : actual)
            for (auto j : tranzitii[i][edge])
                after_step.insert(j);
        return after_step;
    }

    /// marks accesibil[nod] = [node is visible from final_States]
    void solve_inaccesibil() {
        accesibil = vector <int> (tranzitii.size(), 0);
        vector <int> bfs;
        for (auto i: final_states)
            bfs.push_back(i), accesibil[i] = 1;

        for (int it = 0; it < (int)bfs.size(); it++) {
            int nod = bfs[it];
            for (auto i : backward[nod]) {
                if (!accesibil[i]) {
                    accesibil[i] = 1;
                    bfs.push_back(i);
                }
            }
        }
    }
    /// returns if a world is accepted by the automaton
 public:
    Automat() { }
    Automat(int n) : tranzitii(n + 1), backward(n + 1) { }

    void AddEdge(int from, int to, char color) {
        tranzitii[from][color].push_back(to);
        backward[to].push_back(from);
    }

    void AddStartingNode(int nod) {
        initial_states.insert(nod);
    }

    void AddEndingNode(int nod) {
        final_states.insert(nod);
    }
    
    bool IsAccepted(string word) {
        auto actual = initial_states;
        for (auto i : word)
            actual = step(actual, i);

        bool ok = 0;
        for (auto i : actual)
            ok |= (final_states.find(i) != final_states.end());
        return ok;
    }

    /// cele mai mici q cuvinte
    vector <string> SmallestAcceptedStrings(int q = 100) {
        solve_inaccesibil();
        vector <pair <int, string>> bfs;
        set <string> ans;

        for (auto i : initial_states)
            if (accesibil[i])
                bfs.push_back({ i, "" });

        while ((int)ans.size() < q && !bfs.empty()) {
            vector <pair <int, string>> next_step;
            for (auto i : bfs) {
                if (final_states.find(i.first) != final_states.end())
                    ans.insert(i.second);
                
                for (auto edge : tranzitii[i.first])
                    for (auto to : edge.second)
                        if (accesibil[to])
                            next_step.push_back({ to, i.second + edge.first });
            }
            bfs = next_step;
        }

        vector <string> v;
        for (auto i : ans)
            v.push_back(i);

        sort(v.begin(), v.end(), [](const string & a, const string & b) { return a.size() < b.size(); });
        v.resize(min((int)v.size(), q));
        return v;
    }

    /*

    */
    friend istream & operator>> (istream & in, Automat & automat) {
        int n;
        in >> n;

        automat = Automat(n);
        /// citesc muchiile
        int m;
        in >> m;

        while (m--) {
            int a, b;
            char c;
            in >> a >> b >> c;
            automat.AddEdge(a, b, c);
        }

        /// citesc staring node
        int nod;
        in >> nod;
        automat.AddStartingNode(nod);

        /// citesc starile finale
        in >> m;
        while (m--) {
            in >> nod;
            automat.AddEndingNode(nod);
        }

        return in;
    }
};

int main()
{
    Automat automat;
    cin >> automat;

    int n;
    cin >> n;
    
    while (n--) {
        string s;
        cin >> s;
        cout << automat.IsAccepted(s) << '\n';
    }

    auto x = automat.SmallestAcceptedStrings();

    for (auto i : x)
        cout << i + "\n";

    return 0;
}
