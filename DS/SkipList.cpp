#include <bits/stdc++.h>
using namespace std;

/**
 * Skip list DS
**/

class SkipList {
    using T = int;

    typedef struct SkipList::Elem * List;
    static List begin_guard, end_guard;
    struct Elem {
        T val;
        vector <List> next, prev;
        Elem(int grad, T val) : val(val), next(grad, end_guard), prev(grad, begin_guard) { } 
    };
    int grad_max;

    T find(T elem)
    {
        List act = begin_guard;
        int grad_act = grad_max - 1;
        
        while (grad_act >= 0) {
            while (act->next[grad_act]->val <= elem)
                act = act->next[grad_act];
            grad_act--;
        }

        return act;
    }

public:
    SkipList() { }

    SkipList(int n)
    {
        int grad_max = 3;
        while (n /= 2)
            grad_max++;
        begin_guard = new Elem(grad_max, numeric_limits <T>::min());
        end_guard = new Elem(grad_max, numeric_limits <T>::max());
    }

    bool Find(T elem)
    {
        return find(elem)->val == elem;
    }

    void Insert(T elem);

    void Remove(T elem);

    T LastSmallerOrEqual(T elem)
    {
        return find(elem)->val;
    }
    
    T FirstBiggerOrEqual(T elem)
    {
        List act = find(elem);
        return act->next[0]->val;
        
    }

    T First();
    T Last();

};


