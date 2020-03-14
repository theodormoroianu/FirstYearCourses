#include "TreapSort.hpp"

#include <bits/stdc++.h>
using namespace std;

namespace {
    mt19937 rnd(time(0));

    typedef struct Treap * Arbore;
    typedef pair <Arbore, Arbore> Paa;
    Arbore NIL;
    struct Treap {
        int val, g, prio;
        Arbore left, right;
        Treap(int val) : val(val), g(1), prio(rnd()), left(NIL), right(NIL) { }
        ~Treap() {
            if (left != NIL && left)
                delete left;
            if (right != NIL && right)
                delete right;
        }
        void recalc() {
            g = 1 + left->g + right->g;
        }
    };

    Arbore Join(Arbore a, Arbore b)
    {
        if (a == NIL)
            return b;
        if (b == NIL)
            return a;
        if (a->prio > b->prio) {
            a->right = Join(a->right, b);
            a->recalc();
            return a;
        }
        // else
        b->left = Join(a, b->left);
        b->recalc();
        return b;
    }

    Paa Split(Arbore a, int val) 
    {
        /// tot ce e <= val in stanga
        if (a == NIL)
            return { NIL, NIL };
        if (a->val <= val) {
            Paa s = Split(a->right, val);
            a->right = s.first;
            a->recalc();
            return { a, s.second };
        }
        // else
        Paa s = Split(a->left, val);
        a->left = s.second;
        a->recalc();
        return { s.first, a };
    }

    Arbore Insert(Arbore a, int val) 
    {
        Paa s = Split(a, val);
        Arbore new_node = new Treap(val);
        return Join(s.first, Join(new_node, s.second));
    }

    void Dfs(Arbore node, int ans[], int& poz) 
    {
        if (node == NIL)
            return;
        Dfs(node->left, ans, poz);
        ans[poz++] = node->val;
        Dfs(node->right, ans, poz);
    }
}

void TreapSort(int v[], int n)
{
    NIL = new Treap(0);
    NIL->g = 0;
    NIL->left = NIL->right = 0;

    Arbore root = NIL;

    for (int i = 0; i < n; i++)
        root = Insert(root, v[i]);

    int poz = 0;
    Dfs(root, v, poz);

    if (poz != n)
        throw runtime_error("Somehow the treap created / deleted some elements");

    delete root;
    if (n)
        delete NIL;
}