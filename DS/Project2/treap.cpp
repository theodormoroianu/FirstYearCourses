/**
 * NOT TESTED
 * IDK about the predecesor and succesor functions
 */

#include <bits/stdc++.h>
using namespace std;

/**
 * Treap DS
 */
template <class T>
class Treap
{
    static mt19937 rnd;

    struct Node 
    {
        T val, minim, maxim;
        int prio, g;
        Node *st, *dr;
        
        void recalc()
        {
            g = 1;
            minim = maxim = val;
            if (st)
                g += st->g, minim = st->minim;
            if (dr)
                g += dr->g, maxim = dr->maxim;
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

    /// pune tot ce e in dfs in acc
    void dfs(Arbore a, vector <T> & acc)
    {
        if (!a)
            return;
        dfs(a->st);
        acc.push_back(a->val);
        dfs(a->dr);
    }

public:

    /// inserts val into the treap
    void Insert(T val)
    {
        Paa s = split(root, val, 0);
        Arbore node = new Node(val);

        root = join(s.first, join(node, s.second));
    }

    /// returns true if val is inside the treap
    bool Find(T val)
    {
        Paa s1 = split(root, val, 0);
        Paa s2 = split(s1.first, val, 1);

        bool ans = s2.second;
        
        root = join(join(s2.first, s2.second), s1.second);
        return ans;
    }

    /// removes ONE occurence of val from the treap
    void Erase(T val)
    {
        Paa s1 = split(root, val, 0);
        Paa s2 = split(s1.first, val, 1);

        if (!s2.second)
            throw runtime_error("Tried to remove a non-existing value from the treap!");

        root = join(join(s2.first, join(s2.second->st, s2.second->dr)), s1.second);
        s2.second->st = s2.second->dr = 0;
        delete s2.second;    
    }

    /// returns first value smaller than x
    T Predecesor(T val)
    {
        Paa s = split(root, val, 0);
        T ans = s.first->maxim;
        root = join(s.first, s.second);
        return ans;
    }

    /// returns first value bigger than x
    T Succesor(T val)
    {
        Paa s = split(root, val, 1);
        T ans = s.second->minim;
        root = join(s.first, s.second);
        return ans;
    }

    Treap(vector <T> v = { }) : root(0)
    {
        for (auto i : v)
            Insert(i);
    }

    ~Treap()
    {
        if (root)
            delete root;
    }
};

template <class T>
mt19937 Treap<T>::rnd = mt19937(time(0));




int main()
{
    Treap <int> tr;
    tr.Insert(10);
    tr.Insert(12);
    tr.Insert(14);
    tr.Insert(16);
    tr.Erase(14);

    cout << tr.Find(12) << ' ' << tr.Find(13) << ' ' << tr.Find(14) << '\n';

    return 0;
}