#ifndef MIN_MAX_HEAP_
#define MIN_MAX_HEAP_


#include <vector>
#include <functional>
#include <stdexcept>

/**
 * Class T MUST have '<' ans '>' operators
 * 
 * first, third etc levels are min levels, rest are max levels
 */


template <class T>
class MinMaxHeap
{
    std::vector <T> heap_;
    std::vector <bool> lvl_;

    void Build(const std::vector <T> & heap);
    void PushDown(int poz);
    void PushUp(int poz);

public:
    MinMaxHeap(const std::vector <T> & heap);
    MinMaxHeap();
    T GetMinim();
    T GetMaxim();
    T PopMinim();
    T PopMaxim();
    void Insert(T elem);

    std::vector <T> verify(int node = 1);
};


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
        return std::min(heap_[2], heap_[3]);
}


template <class T>
T MinMaxHeap<T>::PopMinim()
{
    T minim = GetMinim();
    std::swap(heap_.back(), heap_[1]);
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

    std::swap(heap_.back(), heap_[nod]);
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
    for (auto i : heap) {
        heap_.push_back(i);
        lvl_.push_back(1 ^ lvl_[lvl_.size() / 2]);
    }
    for (int i = heap_.size() - 1; i >= 1; i--)
        PushDown(i);
}

template <class T>
void MinMaxHeap<T>::PushUp(int poz)
{
    auto cmp = (lvl_[poz] ? [](T a, T b) { return a > b; } : [](T a, T b) { return a < b; });

    if (poz / 2 != 0 && cmp(heap_[poz / 2], heap_[poz])) {/// max heap on poz / 2
        std::swap(heap_[poz], heap_[poz / 2]);
        PushUp(poz / 2);
    }
    else if (poz / 4 != 0 && cmp(heap_[poz], heap_[poz / 4])) { /// min heap on poz / 4
        std::swap(heap_[poz], heap_[poz / 4]);
        PushUp(poz / 4);
    }
}

template <class T>
void MinMaxHeap<T>::PushDown(int poz)
{
    std::vector <int> fii;
    for (int i = 2 * poz; i <= 2 * poz + 1; i++)
        if (i < (int)heap_.size())
            fii.push_back(i);

    for (int i = 4 * poz; i <= 4 * poz + 3; i++)
        if (i < (int)heap_.size())
            fii.push_back(i);

    auto cmp = (lvl_[poz] ? [](T a, T b) { return a > b; } : [](T a, T b) { return a < b; });

    int fiumin = -1;
    for (auto i : fii)
        if (fiumin == -1 || !cmp(heap_[fiumin], heap_[i]))
            fiumin = i;

    if (fiumin != -1 && cmp(heap_[fiumin], heap_[poz])) {
        std::swap(heap_[poz], heap_[fiumin]);
        if (fiumin >= 4 * poz && !cmp(heap_[fiumin], heap_[fiumin / 2]))
            std::swap(heap_[fiumin], heap_[fiumin / 2]);
        PushDown(fiumin);
    }    
}

template <class T>
std::vector <T> MinMaxHeap<T>::verify(int node)
{
    if (node == 1)
        if (lvl_[node] != 0)
            throw std::runtime_error("Node 1 is not min node");

    std::vector <int> act = { heap_[node] };

    if (2 * node < (int)heap_.size()) {
        auto vec = verify(2 * node);
        std::copy(vec.begin(), vec.end(), std::back_inserter(act));
    }
    if (2 * node < (int)heap_.size()) {
        auto vec = verify(2 * node);
        std::copy(vec.begin(), vec.end(), std::back_inserter(act));
    }
    
    std::sort(act.begin(), act.end());

    if (lvl_[node] == 0 && act[0] != heap_[node])
            throw std::runtime_error("Node on min level is not minimal");
    else if (lvl_[node] == 1 && act.back() != heap_[node])
            throw std::runtime_error("Node on max level is not maxima");
    return act;
}


#endif // MIN_MAX_HEAP_