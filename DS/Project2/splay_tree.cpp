/**
 * DOES NOT WORK YET
 * THERE'S MAINLY ONLY THE SPLAY FUNCTION
 * BUT THE REMAINING STUFF IS TOO CANCER
 */


#include <bits/stdc++.h>
using namespace std;

/**
 *  SplayTree class
 */
template <class T>
class SplayTree {
    struct Node {
        int p = 0, c[2] = {0, 0};
        T val = 0;
    };
    vector<Node> S;
    int root;

    int dir(int x, int y)
    {
        return S[x].c[1] == y;
    }
    
    void set(int x, int d, int y)
    {
        if (x)
            S[x].c[d] = y, pull(x);
        if (y)
            S[y].p = x;
    }
    
    void pull(int x) { }
    
    void push(int x) { }
    
    void rotate(int x, int d)
    { 
        int y = S[x].p, z = S[y].p, w = S[x].c[d];
        set(y, !d, w);
        set(x, d, y);
        set(z, dir(z, y), x);
    }
    
    void splay(int x)
    {
        for (push(x); S[x].p; ) {
        int y = S[x].p, z = S[y].p;

        push(z), push(y), push(x);
        
        int dx = dir(y, x), dy = dir(z, y);
        
        if (!z) 
            rotate(x, !dx); 
        else if (dx == dy) 
            rotate(y, !dx), rotate(x, !dx); 
        else
            rotate(x, dy), rotate(x, dx);
        }
    }

    int deep_value(int nod, int dir)
    {
        if (!S[nod].c[dir])
            return nod;
        return deep_value(S[nod].c[dir], dir);
    }

    /// biggest smaller or eq
    int find(int nod, T val)
    {
        if (!nod)
            return 0;
        if (S[nod].val > val)
            return find(S[nod].c[0], val);
        int x = find(S[nod].c[1], val);
        return (x ? x : nod);
    }

public:

    void Insert(T val)
    {
        S.emplace_back();
        S.back().val = val;
        
    }

    SplayTree(vector <T> v) : S(1), root(0)
    {
        for (auto i : v)
            Insert(i);
    }

    ~SplayTree() { }
};