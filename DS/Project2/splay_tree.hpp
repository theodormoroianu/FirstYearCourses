#ifndef SPLAY_TREE_
#define SPLAY_TREE_

#include <bits/stdc++.h>
using namespace std;

template <class T>
class SplayTree
{   
    struct Node {
        T val;
        int poz; /// poz = (this == father->sons[1])
        Node *father, *sons[2];

        Node() : father(0), sons{ 0, 0 } { }
        Node(T val) : val(val), father(0), sons{ 0, 0 } { }

        ~Node() {
            if (sons[0] != 0)
                delete sons[0];
            if (sons[1] != 0)
                delete sons[1];
        }

        void recalc() {
            if (sons[0])
                sons[0]->father = this, sons[0]->poz = 0;
            if (sons[1])
                sons[1]->father = this, sons[1]->poz = 1;
        }
    };
    Node *root;

    void Splay(Node* nod)
    {
        root = nod;
        while (true) {
            if (nod->father == 0)
                return;
            else if (nod->father->father == 0) {
                /// simple rotation
                Node* a = nod->father;
                int t = nod->poz;
                assert(nod == a->sons[t]);

                a->sons[t] = nod->sons[t ^ 1];
                nod->sons[t ^ 1] = a;

                a->recalc();
                nod->recalc();
                nod->father = 0;
            }
            else if (nod->poz == nod->father->poz) {
                /// zig-zig rotation
                Node *a = nod->father, *b = nod->father->father;
                if (b->father)
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
                if (nod->father)
                    nod->father->recalc();
            }
            else {
                /// zig-zag rotation
                Node *a = nod->father, *b = nod->father->father;
                if (b->father)
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
                if (nod->father)
                    nod->father->recalc();    
            }
        }
    }

    bool FindAndSplay(T val)
    {
        Node* ans = root;
        Node* last = 0;

        while (ans) {
            last = ans;
            if (ans->val == val) {
                Splay(ans);
                return true;
            }
            if (ans->val > val)
                last = ans, ans = ans->sons[0];
            else
                last = ans, ans = ans->sons[1];
        }

        if (last)
            Splay(last);

        return false;        
    }

public:
    SplayTree()
    {
        root = 0;
    }

    ~SplayTree()
    {
        if (root)
            delete root;
    }

    void insert(T val)
    {
        Node* nod_nou = new Node(val);
        if (!root) {
            root = nod_nou;
            return;
        }
        
        Node *last = 0, *act = root;
        
        while (act) {
            last = act;
            if (act->val >= val)
                act = act->sons[0];
            else
                act = act->sons[1];
        }
        
        nod_nou->father = last;
        if (last->val >= val)
            last->sons[0] = nod_nou;
        else
            last->sons[1] = nod_nou;
        last->recalc();

        Splay(nod_nou);
    }

    void erase(T val)
    {
        if (!FindAndSplay(val))
            throw runtime_error("Element received with erase is not in SplayTree!");
        Node* left = root->sons[0];
        Node* right = root->sons[1];

        if (left)
            left->father = 0;
        if (right)
            right->father = 0;
            
        root->sons[0] = root->sons[1] = 0;
        delete root;

        if (left == 0) {
            root = right;
            return;
        }

        root = left;
        FindAndSplay(last());

        if (root->sons[1])
            throw runtime_error("Internal Error!");
        
        root->sons[1] = right;
        root->recalc();
    }

    bool find(T val)
    {
        return FindAndSplay(val);
    }

    T first()
    {
        if (root == 0)
            throw runtime_error("SplayTree is empty!");

        Node* ans = root;
        while (ans->sons[0])
            ans = ans->sons[0];

        Splay(ans);

        return ans->val;
    }

    T last()
    {
        if (root == 0)
            throw runtime_error("SplayTree is empty!");

        Node *ans = root;
        while (ans->sons[1])
            ans = ans->sons[1];

        Splay(ans);

        return ans->val;
    }
};

#endif // SPLAY_TREE_