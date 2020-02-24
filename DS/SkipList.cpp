#include <bits/stdc++.h>
using namespace std;

/**
 * Skip list DS
**/

mt19937 rnd(0);

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

    T Last()
    {
        return end_guard->prev[0]->val;
    }

    bool Empty() {
        return begin_guard->next[0] == end_guard;
    }

    friend ostream & operator<< (ostream & out, SkipList & lst) 
    {
        out << "Grad max is " << lst.grad_max << '\n';
        for (int i = lst.grad_max - 1; i >= 0; i--) {
            cout << "Nodes on level " << i << ": ";
            for (auto x = lst.begin_guard->next[i]; x != lst.end_guard; x = x->next[i])
                cout << x->val << ' ';
    
            cout << '\n';
        }
        return out;
    }

};


void Verif()
{
    multiset <int> mst;
    SkipList slst;

    mst.insert(123);
    slst.Insert(123);

    while (true) {
        int x = rnd() % 1000;
        if (rnd() % 3 == 0 && mst.size() > 1) {
            if (mst.find(x) != mst.end())
                mst.erase(mst.find(x));
            slst.Remove(x);
        }
        else if (rnd() % 3 == 0) {
            int x = rnd() % 1000;
            mst.insert(x);
            slst.Insert(x);
        }
        else {
            int x = rnd() % 1000;
            bool found1 = (mst.find(x) != mst.end());
            bool found2 = slst.Find(x);

            if (found1 != found2) {
                cerr << "WA\n";
                exit(0);
            }
        }
        if (rnd() % 10000 == 0)
            cerr << "ok" << endl;
    }

}


int main()
{
    ifstream in("algsort.in");
    ofstream out("algsort.out");

    int n;
    in >> n;

    SkipList sklst(n);

    while (n--) {
        int x;
        in >> x;
        sklst.Insert(x);
    }

    while (!sklst.Empty()) {
        out << sklst.First() << ' ';
        sklst.Remove(sklst.First());
    }


    return 0;
}