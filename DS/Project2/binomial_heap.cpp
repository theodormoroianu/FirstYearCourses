/**
 * DOES NOT WORK YET
 * 
 * WHEN I TRY TO ADD '1' TO IT
 * THE SANITIZER STARTS YELLING AND
 * I HAVE NO IDEEA YET WHAT IS WRONG
 * WITH IT :(
 */



#include <bits/stdc++.h>
using namespace std;


/**
 * Max-Heap DS
 */
template <class T>
class BinomialHeap {
    
    /// degreee of node is size of fii
    struct Node {
        T val;
        vector <Node *> fii;

        Node(int val) : val(val) { }
        ~Node()
        {
            for (auto i : fii)
                if (i)
                    delete i;
        }
    };
    vector <Node *> roots1, roots2;

    Node* join(Node *a, Node *b)
    {
        if (!a)
            return b;
        if (!b)
            return a;
        
        assert(a->fii.size() == b->fii.size());

        if (a->val < b->val)
            swap(a, b);
        a->fii.push_back(b);
        return a;
    }

    void unite(vector <Node *> & v, vector <Node *> aux)
    {
        /// il vars NEAPARAT pe aux in v

        Node *push = 0;
        for (int i = 0; i < (int)aux.size(); i++) {
            if (i >= (int)aux.size())
                throw runtime_error("That's on my idk what tf just happend");

            int cnt = (push != 0) + (v[i] != 0) + (aux[i] != 0);
            if (cnt == 3)
                push = join(push, aux[i]);
            else if(cnt == 2) {
                push = join(push, join(v[i], aux[i]));
                v[i] = 0;
            }
            else {
                v[i] = join(push, join(v[i], aux[i]));
                push = 0;
            }
        }
        if (push)
            v.push_back(push);
    }

    void erase(vector <Node *> & v, int poz)
    {
        auto x = v[poz]->fii;
        v[poz] = 0;
        unite(v, x);
    }

    int poz_min(vector <Node *> v)
    {
        if (v.size() == 0)
            throw runtime_error("Tried to get min on empty heap");
        pair <T, int> act = { v[0]->val, 0 };
        for (int i = 1; i < (int)v.size(); i++)
            act = min(act, make_pair(v[i]->val, i));
        
        return act.second;
    }

    void propagate()
    {
        if (roots1.empty() && !roots2.empty())
            throw runtime_error("You smartass deleted a not-existing value of the heap and now guess\
            what, it broke and that's on you!");
        
        while (!roots2.empty()) {
            int x = poz_min(roots1);
            int y = poz_min(roots2);

            if (roots1[x]->val == roots2[y]->val) {
                erase(roots1, x);
                erase(roots2, y);
            }
            else
                break;
        }
    }

public:

    /// inserts a value in the heap
    void Insert(T val)
    {
        vector <Node *> nou = { new Node(val) };
        unite(roots1, nou);
    }

    /// returns biggest value of the heap
    T Top()
    {
        propagate();
        if (roots1.size() == 0)
            throw runtime_error("Tried to get top from an empty heap");
        return roots1[poz_min(roots1)]->val;
    }

    /// removes the biggest value of the heap and returns it
    T Pop()
    {
        propagate();
        T ans = Top();
        Erase(ans);
        propagate();

        return ans;  
    }

    /// deletes a value from the heap
    void Erase(T val)
    {
        vector <Node *> nou = { new Node(val) };
        unite(roots2, nou);
    }
    
    /// creates a paring heap from a vector
    BinomialHeap(vector <T> a = { })
    {
        for (auto i : a)
            Insert(i);
    }

    ~BinomialHeap()
    {
        for (auto i : roots1)
            delete i;
        for (auto i : roots2)
            delete i;
    }
};

int main()
{
    vector <int> v = { 1, 2, 3 };
    BinomialHeap <int> bh;

    int op;
    cin >> op;

    cout << "Available:\nInsert\nTop\nErase\n";

    while (op --> 0) {
        string s;
        cin >> s;
        if (s[0] == 'I' || s[0] == 'i') {
            int val;
            cin >> val;
            bh.Insert(val);
        }
        else if (s[0] == 'T' || s[0] == 't') {
            cout << "Top = " << bh.Top() << '\n';
        }
        else if (s[0] == 'E' || s[0] == 'e') {
            int val;
            cin >> val;
            bh.Erase(val);
        }
    }

    return 0;
}