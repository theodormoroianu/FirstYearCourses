#ifndef MIN_MAX_HEAP_
#define MIN_MAX_HEAP_

#include <vector>
#include <functional>

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
};

#endif // MIN_MAX_HEAP_