#include <bits/stdc++.h>
#include "SkipList.hpp"
using namespace std;

class SkipList {
    using T = int;
    struct Elem {
        T val;
        vector <Elem *> next, prev;
        Elem(int grad, T val) : val(val), next(grad), prev(grad) { }
    };
    Elem *begin_guard, *end_guard;
    int grad_max;

    Elem * find(T elem)
    {
        Elem * act = begin_guard;
        int grad_act = grad_max - 1;

        while (grad_act >= 0) {
            while (act->next[grad_act]->val <= elem)
                act = act->next[grad_act];
            grad_act--;
        }
        return act;
    }

    int random_grd()
    {
        int gr = 1;
        while (rnd() % 2)
            gr++;
        return min(gr, grad_max);
    }

public:
    SkipList(int n = 100)
    {
        grad_max = 3;
        while (n /= 2)
            grad_max++;
        begin_guard = new Elem(grad_max, numeric_limits <T>::min());
        end_guard = new Elem(grad_max, numeric_limits <T>::max());
        fill(begin_guard->next.begin(), begin_guard->next.end(), end_guard);
        fill(end_guard->prev.begin(), end_guard->prev.end(), begin_guard);
    }

    ~SkipList()
    {
        for (auto i = begin_guard; i != end_guard; ) {
            i = i->next[0];
            delete i->prev[0];
        }
        delete end_guard;
    }

    bool Find(T elem)
    {
        return find(elem)->val == elem;
    }

    void Insert(T elem)
    {
        vector <Elem *> see(grad_max, begin_guard);
        Elem * act = begin_guard;
        int grad_act = grad_max - 1;
        while (grad_act >= 0) {
            while (act->next[grad_act]->val <= elem)
                act = act->next[grad_act];
            see[grad_act] = act;
            grad_act--;
        }

        int my_grad = random_grd();
        Elem * me = new Elem(my_grad, elem);

        for (int i = 0; i < my_grad; i++) {
            me->prev[i] = see[i];
            me->next[i] = see[i]->next[i];
            me->next[i]->prev[i] = me;
            me->prev[i]->next[i] = me;
        }
    }

    void Remove(T elem)
    {
        Elem * act = find(elem);
        if (act->val != elem)
            return;
        for (int i = 0; i < (int)act->next.size(); i++) {
            act->prev[i]->next[i] = act->next[i];
            act->next[i]->prev[i] = act->prev[i];
        }
        delete act;
    }

    T LastSmallerOrEqual(T elem)
    {
        return find(elem)->val;
    }

    T FirstBiggerOrEqual(T elem)
	{
        Elem * act = find(elem);
        return (act->val == elem ? elem : act->next[0]->val);
    }

    T First()
    {
        return begin_guard->next[0]->val;
    }
};


void SkipListSort(int v[], int n)
{
    SkipList sklst(n);
	for (int i = 0; i < n; i++)
        sklst.Insert(v[i]);

	for (int i = 0; i < n; i++) {
        v[i] = sklst.First();
        sklst.Remove(sklst.First());
    }
}
