#include "AVLSort.hpp"
#include <bits/stdc++.h>
using namespace std;

namespace {
    typedef struct AVL * Arbore;
    Arbore NIL;
    struct AVL {
        int val;
        int h;
        Arbore st, dr;
        AVL(int val) : val(val), h(1), st(NIL), dr(NIL) { }
        ~AVL() {
            if (st != NIL && st)
                delete st;
            if (dr != NIL && dr)
                delete dr;
        }
        void recalc() {
            h = 1 + max(st->h, dr->h);
        }
    };

    Arbore Rotation(Arbore node);
    Arbore CWRotation(Arbore node);
    Arbore CCWRotation(Arbore node);

    Arbore Rotation(Arbore node)
    {
        if (node == NIL)
            return node;
        if (abs(node->st->h - node->dr->h) > 2)
            throw runtime_error("In AVL-Tree, a node is too unbalanced.");

        switch (node->st->h - node->dr->h) {
            case -2:
                return CCWRotation(node);
            case 2:
                return CWRotation(node);
            default:
                return node;
        }
    }

    Arbore CWRotation(Arbore node)
    {
        /// totates clockwise around node
        assert(node->st != NIL);
        if (node->st->dr->h > node->st->st->h)
            node->st = CCWRotation(node->st);

        Arbore new_root = node->st;
        node->st = new_root->dr;
        new_root->dr = node;

        node->recalc();
        new_root->recalc();
        return new_root;
    }

    Arbore CCWRotation(Arbore node)
    {
        /// rotates counter clockwise around node
        assert(node->dr != NIL);
        if (node->dr->st->h > node->dr->dr->h)
            node->dr = CWRotation(node->dr);

        Arbore new_root = node->dr;
        node->dr = new_root->st;
        new_root->st = node;

        node->recalc();
        new_root->recalc();
        return new_root;
    }

    Arbore Insert(Arbore root, int val)
    {
        if (root == NIL)
            return new AVL(val);

        if (root->val >= val) {
            root->st = Insert(root->st, val);
            root->recalc();
            return Rotation(root);
        }
        // else
        root->dr = Insert(root->dr, val);
        root->recalc();
        return Rotation(root);
    }

    void Dfs(Arbore node, int ans[], int& poz)
    {
        if (node == NIL)
            return;
        Dfs(node->st, ans, poz);
        ans[poz++] = node->val;
        Dfs(node->dr, ans, poz);
    }
}

void AVLSort(int v[], int n)
{
    NIL = new AVL(0);
    NIL->h = 0;
    NIL->st = NIL->dr = 0;

    Arbore root = NIL;

    for (int i = 0; i < n; i++)
        root = Insert(root, v[i]);

    int poz = 0;
    Dfs(root, v, poz);

    if (poz != n)
        throw runtime_error("AVL Created or destroyed too many elements");

    delete root;
    if (n)
        delete NIL;
}