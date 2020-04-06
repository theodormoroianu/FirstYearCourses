#ifndef TREAP_
#define TREAP_

#include <random>
#include <time.h>
#include <functional>

template <class T>
class Treap
{
    std::mt19937 rnd;

    struct Node 
    {
        T val;
        int prio, g;
        Node *st, *dr;
        
        void recalc()
        {
            g = 1 + st->g + dr->g;
        }

        Node(T val) : val(val), g(1) { }
    } *NIL, *root;

    using Arbore = Node*;
    using Paa = std::pair <Arbore, Arbore>;

    Arbore new_node(T val)
    {
        Arbore ans = new Node(val);
        ans->st = ans->dr = NIL;
        ans->prio = rnd();

        return ans;
    }

    Arbore join(Arbore a, Arbore b)
    {
        if (a == NIL)
            return b;
        if (b == NIL)
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
        if (a == NIL)
            return { NIL, NIL };
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

public:

    void insert(T val)
    {
        Paa s = split(root, val, 0);
        Arbore node = new_node(val);

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

        root = join(join(s2.first, join(s2.second->st, s2.second->dr)), s1.second);
        if (s2.second != NIL)
            delete s2.second;
    }

    Treap()
    {
        rnd = std::mt19937(time(0));
        NIL = new Node(T());
        NIL->g = 0;
        NIL->st = NIL->dr = NIL;
        root = NIL;
    }

    ~Treap()
    {
        std::function<void(Arbore)> remover = [&](Arbore x)
        {
            if (x == NIL)
                return;
            remover(x->st);
            remover(x->dr);
            delete x;
        };
        if (root != NIL)
            remover(root);
        delete NIL;
    }

};

#endif // TREAP_