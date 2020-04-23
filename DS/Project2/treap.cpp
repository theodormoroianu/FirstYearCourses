#include <bits/stdc++.h>
using namespace std;

template <class T>
class Treap
{
    mt19937 rnd;

    struct Node 
    {
        T val;
        int prio, g;
        Node *st, *dr;
        
        void recalc()
        {
            g = 1 + st->g + dr->g;
        }

        Node(T val) : val(val), g(1), st(0), dr(0)
        {
            prio = rnd();
        }
        ~Node()
        {
            if (st)
                delete st;
            if (dr)
                delete dr;
        }
    } *root;

    using Arbore = Node*;
    using Paa = std::pair <Arbore, Arbore>;

    Arbore join(Arbore a, Arbore b)
    {
        if (!a)
            return b;
        if (!b)
            return a;
        if (a->prio > b->prio) {
            a->dr = join(a->dr, b);
            a->recalc();
            return a;
        }
        /// else
        b->st = join(a, b->st);
        b->recalc();
        return b;
    }

    /// in stanga tot ce e <= (strict = 0) / tot ce e < (strict = 1) 
    Paa split(Arbore a, T val, bool strict)
    {
        if (!a)
            return { 0, 0 };
        if (a->val < val || (a->val == val && !strict)) {
            Paa dr = split(a->dr, val, strict);
            a->dr = dr.first;
            a->recalc();
            return { a, dr.second };
        }
        /// else
        Paa st = split(a->st, val, strict);
        a->st = st.second;
        a->recalc();
        return { st.first, a };
    }

    void dfs(Arbore a, vector <T> & acc)
    {
        if (!a)
            return;
        dfs(a->st);
        acc.push_back(a->val);
        dfs(a->dr);
    }

public:

    void insert(T val)
    {
        Paa s = split(root, val, 0);
        Arbore node = new Node(val);

        root = join(s.first, join(node, s.second));
    }

    bool find(T val)
    {
        Paa s1 = split(root, val, 0);
        Paa s2 = split(s1.first, val, 1);

        bool ans = (s2.second != NIL);
        
        root = join(join(s2.first, s2.second), s1.second);
        return ans;
    }

    void erase(T val)
    {
        Paa s1 = split(root, val, 0);
        Paa s2 = split(s1.first, val, 1);

        assert(s2.second);

        root = join(join(s2.first, join(s2.second->st, s2.second->dr)), s1.second);
        s2.second->st = s2.second->dr = 0;
        delete s2.second;    
    }

    Treap()
    {
        rnd = std::mt19937(time(0));
        root = 0;
    }

    ~Treap()
    {
        if (root)
            delete root;
    }

};
