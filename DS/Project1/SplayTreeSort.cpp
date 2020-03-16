#include  "SplayTreeSort.hpp"
#include <bits/stdc++.h>
using namespace std;

namespace {
    
    typedef struct SplayTree * Arbore;
    Arbore NIL;
    struct SplayTree {
        int val, poz; /// poz = (this == father->sons[1])
        Arbore father, sons[2];

        SplayTree(int val) : val(val), poz(0), father(NIL), sons{ NIL, NIL } { }
        ~SplayTree() {
            if (this == NIL)
                return;
            if (sons[0] != NIL)
                delete sons[0];
            if (sons[1] != NIL)
                delete sons[1];
        }

        void recalc() {
            if (this == NIL)
                return;
            sons[0]->father = sons[1]->father = this;
            sons[0]->poz = 0;
            sons[1]->poz = 1;
        }
    };

    void Splay(Arbore nod)
    {
        while (true) {
            if (nod->father == NIL)
                return;
            else if (nod->father->father == NIL) {
                /// simple rotation
                Arbore a = nod->father;
                int t = nod->poz;
                assert(nod == a->sons[t]);

                a->sons[t] = nod->sons[t ^ 1];
                nod->sons[t ^ 1] = a;

                a->recalc();
                nod->recalc();
                nod->father = NIL;
            }
            else if (nod->poz == nod->father->poz) {
                /// zig-zig rotation
                Arbore a = nod->father, b = nod->father->father;
                b->father->sons[b->poz] = nod;
                nod->father = b->father;

                int t = nod->poz;
                a->sons[t] = nod->sons[t ^ 1];
                nod->sons[t ^ 1] = a;
                b->sons[t] = a->sons[t ^ 1];
                a->sons[t ^ 1] = b;
                
                nod->recalc();
                a->recalc();
                b->recalc();
                nod->father->recalc();
            }
            else {
                /// zig-zag rotation
                Arbore a = nod->father, b = nod->father->father;
                b->father->sons[b->poz] = nod;
                nod->father = b->father;

                int t = nod->poz;

                b->sons[t ^ 1] = nod->sons[t];
                nod->sons[t] = b;

                a->sons[t] = nod->sons[t ^ 1];
                nod->sons[t ^ 1] = a;

                nod->recalc();
                a->recalc();
                b->recalc();
                nod->father->recalc();    
            }
        }
    }

    Arbore Insert(Arbore root, int val)
    {
        Arbore nod_nou = new SplayTree(val);
        if (root == NIL)
            return nod_nou; /// single-noded BST
        
        Arbore last = NIL;
        while (root != NIL) {
            last = root;
            if (root->val >= val)
                root = root->sons[0];
            else
                root = root->sons[1];
        }
        
        nod_nou->father = last;
        if (last->val >= val)
            last->sons[0] = nod_nou;
        else
            last->sons[1] = nod_nou;
        last->recalc();

        Splay(nod_nou);
        return nod_nou;
    }

    void Dfs(Arbore node, int ans[], int& poz) 
    {
        if (node == NIL)
            return;
        Dfs(node->sons[0], ans, poz);
        ans[poz++] = node->val;
        Dfs(node->sons[1], ans, poz);
    }
}

void SplayTreeSort(int v[], int n)
{
    NIL = new SplayTree(0);
    NIL->sons[0] = NIL->sons[1] = 0;

    Arbore root = NIL;

    for (int i = 0; i < n; i++)
        root = Insert(root, v[i]);

    int poz = 0;
    Dfs(root, v, poz);

    if (poz != n)
        throw runtime_error("Somehow the treap created / deleted some elements");

    assert(root != NIL);
    delete root;
    if (n)
        delete NIL;
}