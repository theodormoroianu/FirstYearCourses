#include "min_max_heap.hpp"
#include "splay_tree.hpp"
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
    set <int> s;

    for (int i = 0; i < 10; i++) {
        
    }

}

int main()
{
    TestSplayTree();
    return 0;
}
