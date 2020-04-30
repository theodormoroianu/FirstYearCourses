#include <bits/stdc++.h>
using namespace std;

/**
 * Implementation of the MinMaxMerge heap DS
 * Class T MUST have '<' ans '>' operators
 * 
 * first, third etc levels are min levels, rest are max levels
 */
template <class T>
class MinMaxHeap
{
    /// element container and level indicator
    std::vector <T> heap_;
    std::vector <bool> lvl_;

    /// builds the heap from a vector
    void Build(const std::vector <T> & heap)
    {
        for (auto i : heap) {
            heap_.push_back(i);
            lvl_.push_back(1 ^ lvl_[lvl_.size() / 2]);
        }
        for (int i = heap_.size() - 1; i >= 1; i--)
            PushDown(i);
    }

    /// pushes the element heap_[poz] down
    void PushDown(int poz)
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
    
    /// pushes the element heap_[poz] up
    void PushUp(int poz)
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


public:

    /// constructs a new MMH containing heap[..] elements
    MinMaxHeap(const std::vector <T> & heap) : heap_(1), lvl_{ 1 }
    {
        Build(heap);
    }

    /// basic constructor
    MinMaxHeap() : heap_(1), lvl_{ 1 } { }

    /// returns min value of the heap
    T GetMinim()
    {
        if (heap_.size() == 1)
            throw std::runtime_error("Tried to get minimum from an empty heap!");
        return heap_[1];
    }

    /// returns max value of the heap
    T GetMaxim()
    {
        if (heap_.size() == 1)
            throw std::runtime_error("Tried to get maximum from an empty heap!");
        if (heap_.size() == 2)
            return heap_[1];
        if (heap_.size() == 3)
            return heap_[2];
        else
            return std::max(heap_[2], heap_[3]);
    }

    /// pops and returns the min value of the heap
    T PopMinim()
    {
        T minim = GetMinim();
        std::swap(heap_.back(), heap_[1]);
        heap_.pop_back();
        lvl_.pop_back();

        PushDown(1);
        return minim;
    }

    /// pops and returns max value of the heap
    T PopMaxim()
    {
        T maxim = GetMaxim();
        
        int nod = 1;
        while (heap_[nod] != maxim)
            nod++;

        std::swap(heap_.back(), heap_[nod]);
        heap_.pop_back();
        lvl_.pop_back();

        PushDown(nod);
        return maxim;
    }

    /// inserts a new value to the heap
    void Insert(T elem)
    {
        int poz = heap_.size();
        heap_.push_back(elem);
        lvl_.push_back(1 ^ lvl_[poz / 2]);

        PushUp(poz);
    }


    /// DEBUG FUNCTION DO NOT USE
    std::vector <T> verify(int node = 1)
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
};


void tester()
{
    mt19937 rnd(time(0));
    while (true) {
        multiset <int> s;
        MinMaxHeap <int> mmh;
        for (int _ = 0; _ < 10000; _++) {
            int op = rnd() % 3;
            if (op == 0) {
                if (rnd() % 10)
                    cerr << "?";
                /// find min
                if (rnd() % 2) {
                    if (!s.empty() && *s.begin() != mmh.GetMinim()) {
                        cerr << "WA\n";
                        exit(0);
                    }
                }
                else {
                    if (!s.empty() && *prev(s.end()) != mmh.GetMaxim()) {
                        cerr << "WA\n";
                        exit(0);
                    }
                }
            }
            else if (op == 1) {
                if (rnd() % 10)
                    cerr << "+";
                int v = rnd() % 100;
                s.insert(v);
                mmh.Insert(v);
            }
            else {
                if (rnd() % 10)
                    cerr << "-";
                if (s.empty())
                    continue;

                if (rnd() % 2) {
                    s.erase(s.begin());
                    mmh.PopMinim();
                }
                else {
                    s.erase(prev(s.end()));
                    mmh.PopMaxim();
                }
            }
        }
        cerr << "\nOK\n\n\n";
    }
}

int main()
{
    // tester();
    MinMaxHeap <int> mmh;
    int N;
    cin >> N;

    while (N--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            mmh.Insert(x);
        }
        else if (op == 2)
            mmh.PopMinim();
        else if (op == 3)
            mmh.PopMaxim();
        else if (op == 4)
            cout << mmh.GetMinim() << '\n';
        else if (op == 5)
            cout << mmh.GetMaxim() << '\n';
        else if (op == 6) {
            int n;
            cin >> n;
            vector <int> v(n);
            for (auto & i : v)
                cin >> i;
            mmh = MinMaxHeap<int>(v);
        }
    }

    return 0;
}
