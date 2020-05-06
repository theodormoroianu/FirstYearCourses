#include "DFA.hpp"
#include "NFA.hpp"
#include "regex.hpp"
#include "unit_tests.hpp"
#include <bits/stdc++.h>
using namespace std;

namespace {
    mt19937 rnd(time(0));

    void NFAToDFA()
    {
        cerr << "Starting NFA-To-DFA unit test ... ";
        bool ok = 1;

        vector <map <char, set <int>>> nfa_edges = {
            { { '\0', { 1, 3 } } },
            { { 'a', { 2 } }, { 'b', { 1 } } },
            { { 'a', { 1 } }, { 'b', { 2 } } },
            { { 'a', { 3 } }, { 'b', { 4 } } },
            { { 'a', { 4 } }, { 'b', { 5 } } },
            { { 'a', { 5 } }, { 'b', { 3 } } }
        };

        NFA nfa(nfa_edges, 0, { 1, 3 });

        vector <map <char, int>> dfa_edges = {
            { { 'a', 3 }, { 'b', 4 } },
            { { 'a', 2 }, { 'b', 0 } },
            { { 'a', 1 }, { 'b', 3 } },
            { { 'a', 0 }, { 'b', 5 } },
            { { 'a', 5 }, { 'b', 1 } },
            { { 'a', 4 }, { 'b', 2 } }
        };

        DFA dfa(dfa_edges, 0, { 0, 1, 3, 4 });

        DFA to_dfa = static_cast <DFA> (nfa);

        ok = (to_dfa == dfa);
        cerr << (ok ? "Pass\n" : "Fail\n");
    }

    void DFAIsAccepted()
    {
        cerr << "Starting DFA-Is-Accepted unit test ... ";
        bool ok = 1;

        vector <map <char, int>> dfa_edges = {
            { { 'a', 3 }, { 'b', 4 } },
            { { 'a', 2 }, { 'b', 0 } },
            { { 'a', 1 }, { 'b', 3 } },
            { { 'a', 0 }, { 'b', 5 } },
            { { 'a', 5 }, { 'b', 1 } },
            { { 'a', 4 }, { 'b', 2 } }
        };

        DFA dfa(dfa_edges, 0, { 0, 1, 3, 4 });

        ok &= (dfa.IsAccepted(""));
        ok &= (dfa.IsAccepted("abababab"));
        ok &= (dfa.IsAccepted("aaabbb"));
        ok &= (dfa.IsAccepted("a"));
        ok &= (!dfa.IsAccepted("ab"));
        ok &= (!dfa.IsAccepted("ababa"));
        ok &= (!dfa.IsAccepted("aaabbaabbb"));

        cerr << (ok ? "Pass\n" : "Fail\n");
    }

    void DFAMinimize()
    {
        cerr << "Starting DFA-Minimize unit test ... ";
        bool ok = 1;

        vector <map <char, int>> dfa_edges_minimized = {
            { { 'a', 3 }, { 'b', 4 } },
            { { 'a', 2 }, { 'b', 0 } },
            { { 'a', 1 }, { 'b', 3 } },
            { { 'a', 0 }, { 'b', 5 } },
            { { 'a', 5 }, { 'b', 1 } },
            { { 'a', 4 }, { 'b', 2 } }
        };

        vector <map <char, int>> dfa_edges = {
            { { 'a', 3 }, { 'b', 4 } },
            { { 'a', 2 }, { 'b', 0 } },
            { { 'a', 1 }, { 'b', 3 } },
            { { 'a', 0 }, { 'b', 5 } },
            { { 'a', 5 }, { 'b', 1 } },
            { { 'a', 4 }, { 'b', 2 } },
            { { 'a', 3 }, { 'b', 4 } }
        };

        DFA minimized(dfa_edges_minimized, 0, { 0, 1, 3, 4 });
        DFA normal(dfa_edges, 6, { 0, 1, 3, 4, 6 });
        normal = normal.Minimize();

        ok &= (minimized.CountStates() == normal.CountStates());
        ok &= (minimized == normal);
        
        cerr << (ok ? "Pass\n" : "Fail\n");
    }

    void DFANegation()
    {
        cerr << "Starting DFA-Negation unit test ... ";
        bool ok = 1;

        vector <map <char, int>> dfa_edges = {
            { { 'a', 3 }, { 'b', 4 } },
            { { 'a', 2 }, { 'b', 0 } },
            { { 'a', 1 }, { 'b', 3 } },
            { { 'a', 0 }, { 'b', 5 } },
            { { 'a', 5 }, { 'b', 1 } },
            { { 'a', 4 }, { 'b', 2 } }
        };

        DFA dfa(dfa_edges, 0, { 0, 1, 3, 4 });
        DFA neg = ~dfa;

        ok &= (dfa.IsAccepted("") != neg.IsAccepted(""));
        ok &= (dfa.IsAccepted("abab") != neg.IsAccepted("abab"));
        ok &= (dfa.IsAccepted("aaa") != neg.IsAccepted("aaa"));
        ok &= (dfa.IsAccepted("AAbbb") != neg.IsAccepted("AAbbb"));
        ok &= (dfa.IsAccepted("C") != neg.IsAccepted("C"));
        ok &= (dfa.IsAccepted("b") != neg.IsAccepted("b"));
        
        cerr << (ok ? "Pass\n" : "Fail\n");
    }

    void DFAIsEqual()
    {
        cerr << "Starting DFA-is-Equal unit test ... ";
        bool ok = 1;

        vector <map <char, int>> dfa_edges = {
            { { 'a', 3 }, { 'b', 4 } },
            { { 'a', 2 }, { 'b', 0 } },
            { { 'a', 1 }, { 'b', 3 } },
            { { 'a', 0 }, { 'b', 5 } },
            { { 'a', 5 }, { 'b', 1 } },
            { { 'a', 4 }, { 'b', 2 } }
        };

        vector <map <char, int>> dfa2_edges = {
            { { 'a', 3 }, { 'b', 4 } },
            { { 'a', 2 }, { 'b', 0 } },
            { { 'a', 1 }, { 'b', 3 } },
            { { 'a', 0 }, { 'b', 5 } },
            { { 'a', 5 }, { 'b', 1 } },
            { { 'a', 4 }, { 'b', 2 } },
            { { 'a', 3 }, { 'b', 4 } }
        };
        
        auto cnt = dfa2_edges;
        vector <int> perm(7);
        iota(perm.begin(), perm.end(), 0);
        shuffle(perm.begin(), perm.end(), rnd);

        for (int i = 0; i < 7; i++)
            cnt[perm[i]] = dfa2_edges[i];
        
        for (auto & i : cnt)
            for (auto & j : i)
                j.second = perm[j.second];

        DFA a(dfa_edges, 0, { 0, 1, 3, 4 });
        DFA b(cnt, perm[6], { perm[0], perm[1], perm[3], perm[4], perm[6] });
        
        ok &= (a == b);

        a = DFA(dfa_edges, 0, { 0, 1, 2, 3, 4 });

        ok &= (a != b);

        cerr << (ok ? "Pass\n" : "Fail\n");
    }

    void DFAIntersection()
    {
        cerr << "Starting DFA-Intersection unit test ... ";
        bool ok = 1;

        /// dfa recognizing paterns with 2k a and 3k b        
        vector <map <char, int>> dfa_edges = {
            { { 'a', 3 }, { 'b', 4 } },
            { { 'a', 2 }, { 'b', 0 } },
            { { 'a', 1 }, { 'b', 3 } },
            { { 'a', 0 }, { 'b', 5 } },
            { { 'a', 5 }, { 'b', 1 } },
            { { 'a', 4 }, { 'b', 2 } }
        };
        
        vector <map <char, int>> dfa2_edges = {
            { { 'a', 1 }, { 'b', 0 } },
            { { 'a', 0 }, { 'b', 1 } }
        };
        vector <map <char, int>> dfa3_edges = {
            { { 'a', 0 }, { 'b', 1 } },
            { { 'a', 1 }, { 'b', 2 } },
            { { 'a', 2 }, { 'b', 0 } }
        };

        DFA total(dfa_edges, 0, { 0 });
        DFA a(dfa2_edges, 0, { 0 });
        DFA b(dfa3_edges, 0, { 0 });

        ok &= (total == (a & b));

        b = DFA(dfa3_edges, 0, { 0, 2 });

        ok &= (total != (a & b));

        cerr << (ok ? "Pass\n" : "Fail\n");
    }

    void DFAReunion()
    {
        cerr << "Starting DFA-Reunion unit test ... ";
        bool ok = 1;

        /// dfa recognizing paterns with 2k a and 3k b        
        vector <map <char, int>> dfa_edges = {
            { { 'a', 3 }, { 'b', 4 } },
            { { 'a', 2 }, { 'b', 0 } },
            { { 'a', 1 }, { 'b', 3 } },
            { { 'a', 0 }, { 'b', 5 } },
            { { 'a', 5 }, { 'b', 1 } },
            { { 'a', 4 }, { 'b', 2 } }
        };
        
        vector <map <char, int>> dfa2_edges = {
            { { 'a', 1 }, { 'b', 0 } },
            { { 'a', 0 }, { 'b', 1 } }
        };
        vector <map <char, int>> dfa3_edges = {
            { { 'a', 0 }, { 'b', 1 } },
            { { 'a', 1 }, { 'b', 2 } },
            { { 'a', 2 }, { 'b', 0 } }
        };

        DFA total(dfa_edges, 0, { 0, 1, 3, 4 });
        DFA a(dfa2_edges, 0, { 0 });
        DFA b(dfa3_edges, 0, { 0 });

        ok &= (total == (a | b));

        b = DFA(dfa3_edges, 0, { 0, 2 });

        ok &= (total != (a | b));

        cerr << (ok ? "Pass\n" : "Fail\n");
    }

    namespace MinimizationTester {
        void tester(DFA x, int sigma)
        {
            DFA minim = x.Minimize();

            for (int _ = 0; _ < 10000; _++) {
                string s;
                int l = rnd() % 8;
                for (int i = 0; i < l; i++)
                    s += 'a' + rnd() % sigma;

                if (x.IsAccepted(s) ^ minim.IsAccepted(s)) {
                    cerr << "\nError for " << s << '\n';
                    cerr << "X.IsAccepted(" << s << ") = " << x.IsAccepted(s) << "\nBut minim.IsAccepted(" << s << ") = ";
                    cerr << minim.IsAccepted(s) << "!!\n";
                    cerr << "Initial DFA: " << x << '\n' << "Minimized DFA: " << minim << '\n';
                    exit(0);
                }
            }
        }

        DFA make_random(int sigma)
        {
            int start_node = 0;
            int l = rnd() % 15 + 1;
            set <int> end_nodes = { (int)(rnd() % l), (int)(rnd() % l) };
            vector <map <char, int>> edges(l);
            for (int i = 0; i < 2 * l * l; i++) {
                char c = rnd() % sigma + 'a';
                edges[rnd() % l][c] = rnd() % l;
            }

            return DFA(edges, start_node, end_nodes);
        }

        void Tester() 
        {
            cerr << "Starting DFA-Minimization stress test ... ";
            auto time_act = chrono::system_clock::now();
            while (1) {
                DFA r = make_random(4);
                tester(r, 4);
                auto now = chrono::system_clock::now();
                if (chrono::duration_cast<chrono::seconds>(now - time_act).count() > 1) {
                    cerr << "Pass\n";
                    return;
                }
            }
        }
    }


    void RegexToDFA()
    {
        cerr << "Starting RegexToDFA unit test ... ";
        bool ok = 1;

        string reg = "((b*)a(b*)a(b*)*)|(a*(d|e))";

        DFA ans = Regex(reg).ToDfa();

        ok &= (ans.IsAccepted("babbbaaa"));
        ok &= (ans.IsAccepted("aaaa"));
        ok &= (!ans.IsAccepted("aaaaa"));
        ok &= (!ans.IsAccepted("aaabbaba"));
        ok &= (ans.IsAccepted(""));
        ok &= (ans.IsAccepted("aad"));
        ok &= (ans.IsAccepted("aaae"));
        ok &= (!ans.IsAccepted("aaade"));
        ok &= (!ans.IsAccepted("b"));
        
        cerr << (ok ? "Pass\n" : "Fail\n");
    }

    void RegexFromDFA()
    {
        cerr << "Starting RegexFromDFA unit test ... ";
        bool ok = 1;
        
        /// dfa recognizing paterns with 2k a and 3k b        
        vector <map <char, int>> dfa_edges = {
            { { 'a', 3 }, { 'b', 4 } },
            { { 'a', 2 }, { 'b', 0 } },
            { { 'a', 1 }, { 'b', 3 } },
            { { 'a', 0 }, { 'b', 5 } },
            { { 'a', 5 }, { 'b', 1 } },
            { { 'a', 4 }, { 'b', 2 } }
        };
        
        DFA x(dfa_edges, 0, { 0 });
        Regex reg(x);
        DFA x2 = reg.ToDfa();

        ok &= (x == x2);

        x = DFA(dfa_edges, 0, { 0, 1, 2, 3 });
        reg = Regex(x);
        x2 = reg.ToDfa();
        
        ok &= (x == x2);

        cerr << (ok ? "Pass\n" : "Fail\n");
    }
}

void UnitTests()
{
    NFAToDFA();
    DFAIsAccepted();
    DFAMinimize();
    DFANegation();
    DFAIsEqual();
    DFAIntersection();
    DFAReunion();
    MinimizationTester::Tester();
    RegexToDFA();
    RegexFromDFA();
}
