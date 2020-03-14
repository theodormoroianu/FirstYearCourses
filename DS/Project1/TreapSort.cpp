#include "TreapSort.hpp"

#include <bits/stdc++.h>
using namespace std;

namespace {
    mt19937 rnd(time(0));

    typedef struct Treap * Arbore;
    typedef pair <Arbore, Arbore> Paa;
    Arbore NIL;
    struct Treap {
        int val, g;
        Arbore left, right;
        
    }
}