#include "min_max_heap.hpp"

#include <stdexcept>

template <class T>
MinMaxHeap<T>::MinMaxHeap() : heap_(1), lvl_{ 1 } { }

template <class T>
MinMaxHeap<T>::MinMaxHeap(const std::vector <T> & heap) : heap_(1), lvl_{ 1 }
{
    Build(heap);
}

template <class T>
T MinMaxHeap<T>::GetMinim()
{
    if (heap_.size() == 1)
        throw std::runtime_error("Tried to get minimum from an empty heap!");
    return heap_[1];
}

template <class T>
T MinMaxHeap<T>::GetMaxim()
{
    if (heap_.size() == 1)
        throw std::runtime_error("Tried to get maximum from an empty heap!");
    if (heap_.size() == 2)
        return heap_[1];
    if (heap_.size() == 3)
        return heap_[2];
    else
        return min(heap_[2], heap_[3]);
}


template <class T>
T MinMaxHeap<T>::PopMinim()
{
    T minim = GetMinim();
    swap(heap_.back(), heap_[1]);
    heap_.pop_back();
    lvl_.pop_back();

    PushDown(1);
    return minim;
}

template <class T>
T MinMaxHeap<T>::PopMaxim()
{
    T minim = GetMaxim();
    
    int nod = 1;
    while (heap_[nod] != minim)
        nod++;

    swap(heap_.back(), heap_[nod]);
    heap_.pop_back();
    lvl_.pop_back();

    PushDown(nod);
    return minim;
}

template <class T>
void MinMaxHeap<T>::Insert(T elem)
{
    int poz = heap_.size();
    heap_.push_back(elem);
    lvl_.push_back(1 ^ lvl_[poz / 2]);

    PushUp(poz);
}

template <class T>
void MinMaxHeap<T>::Build(const std::vector <T> & heap)
{
    for (auto i : heap)
        Insert(i);
    /// TODO: Build in O(n) time
}

template <class T>
void MinMaxHeap<T>::PushUp(int poz)
{
    for (bool modif = 1; (modif ^= 1) == 0; ) {
        if (lvl_[poz] == 0 && poz / 2 >= 1 && heap_[poz])
    }
}



