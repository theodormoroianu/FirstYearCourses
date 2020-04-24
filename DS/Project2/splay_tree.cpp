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
    vector<Node> T;

    int dir(int x, int y)
    {
        return T[x].c[1] == y;
    }
    
    void set(int x, int d, int y) {
        if (x)
            T[x].c[d] = y, pull(x);
        if (y)
            T[y].p = x;
    }
    
    void pull(int x) {
    }
    
    void push(int x) {
    }
    
    void rotate(int x, int d) { 
        int y = T[x].p, z = T[y].p, w = T[x].c[d];
        set(y, !d, w);
        set(x, d, y);
        set(z, dir(z, y), x);
    }
    
    void splay(int x) { 
        for (push(x); T[x].p; ) {
        int y = T[x].p, z = T[y].p;

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

public:
    SplayTree()
    {
        
    }

};