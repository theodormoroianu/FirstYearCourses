#include "min_max_heap.hpp"
#include "splay_tree.hpp"
#include "pairing_heap.hpp"
#include <iostream>
#include <random>
#include <chrono>
#include <vector>

using std::cout;
std::mt19937 rnd(0);

void TestMinMaxHeap()
{

    std::vector <int> v(400);
    
    for (auto & i : v)
        i = rnd() % 100;

    MinMaxHeap <int> mmh(v);
        
    for (int i = 1; i <= 400; i++)
        mmh.Insert(rnd());

    mmh.verify(1);

}


void TestSplayTree()
{
    SplayTree <int> sp;
    multiset <int> s;

    for (int i = 0; i < 100000; i++) {
        int a = rnd() % 500;

        if ((s.find(a) != s.end()) ^ sp.find(a))
            throw runtime_error("set and SplayTree aren't eq!");

        if (s.find(a) != s.end() && rnd() % 2)
            s.erase(s.find(a)), sp.erase(a);
        else
            s.insert(a), sp.insert(a);
    }
    cerr << "OK\n";
}

void TestPairingHeap()
{
    priority_queue <int> pq;
    PairingHeap <int> ph;

    for (int i = 0; i < 10000; i++) {
        int val = rnd() % 500;
        if (ph.empty() ^ pq.empty())
            throw runtime_error("Heaps don't have the same size!");
        if (!ph.empty() && ph.top() != pq.top())
            throw runtime_error("Heaps don't have the same minimum!");

        ph.push(val);
        pq.push(val);

        if (rnd() % 2)
            ph.pop(), pq.pop();
    }

    cerr << "OK\n";
}

int main()
{
    //TestSplayTree();
    TestPairingHeap();

    return 0;
}
