#include <bits/stdc++.h>
using namespace std;


struct SplayTree {
    struct Node {
        int p = 0, c[2] = {0, 0}, pp = 0;
        bool flip = 0;
        int val = 0, dp = 0;
    };
    vector <Node> T;
    vector <int> deleted;

    int dir(int x, int y)
    {
        return T[x].c[1] == y;
    }
    
    void set(int x, int d, int y)
    {
        if (x)
            T[x].c[d] = y, pull(x);
        if (y)
            T[y].p = x;
    }
    
    void pull(int x) {
        if (!x) return;
        int &l = T[x].c[0], &r = T[x].c[1];
        T[x].dp = max({T[x].val, T[l].dp, T[r].dp});
    }
    
    void push(int x) {
        if (!x || !T[x].flip) return;
        int &l = T[x].c[0], &r = T[x].c[1];
        swap(l, r); T[l].flip ^= 1; T[r].flip ^= 1;
        T[x].flip = 0;
    }
    
    void rotate(int x, int d) { 
        int y = T[x].p, z = T[y].p, w = T[x].c[d];
        swap(T[x].pp, T[y].pp);
        set(y, !d, w);
        set(x, d, y);
        set(z, dir(z, y), x);
    }
    
    void splay(int x) { 
        for (push(x); T[x].p;) {
        int y = T[x].p, z = T[y].p;
        push(z); push(y); push(x);
        int dx = dir(y, x), dy = dir(z, y);
        if (!z) 
            rotate(x, !dx); 
        else if (dx == dy) 
            rotate(y, !dx), rotate(x, !dx); 
        else
            rotate(x, dy), rotate(x, dx);
        }
    }
    
};