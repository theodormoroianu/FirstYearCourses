#include <bits/stdc++.h>
using namespace std;


/**
 * Min-Heap DS
 */
template <class T>
class PairingHeap {
    
    struct Node {
        T val;
        vector <Node *> fii;

        Node(T val) : val(val) { }
        ~Node()
        {
            for (auto i : fii)
                delete i;
        }
    } *root1, *root2;

    Node* join(Node *a, Node *b)
    {
        if (!a)
            return b;
        if (!b)
            return a;
        if (a->val > b->val)
            swap(a, b);
        a->fii.push_back(b);
        return a;
    }

    Node* pop(Node *a)
    {
        Node *ans = 0;
        for (int i = 0; i < (int)a->fii.size(); i += 2) {
            if (i + 1 < (int)a->fii.size())
                ans = join(ans, join(a->fii[i], a->fii[i + 1]));
            else
                ans = join(ans, a->fii[i]);
        }

        a->fii.clear();
        delete a;
        return ans;
    }

    void propagate()
    {
        if (root2 && !root1)
            throw runtime_error("You smartass deleted a not-existing value of the heap and now guess\
            what, it broke and that's on you!");
        
        while (root2 && root2->val == root1->val) {
            root2 = pop(root2);
            root1 = pop(root1);
        }
    }

public:

    /// inserts a value in the heap
    void Insert(T val)
    {
        Node *nou = new Node(val);
        root1 = join(root1, nou);
    }

    /// returns biggest value of the heap
    T Top()
    {
        propagate();
        if (root1 == nullptr)
            throw runtime_error("Tried to get top from an empty heap");
        return root1->val;
    }

    /// removes the biggest value of the heap and returns it
    T Pop()
    {
        propagate();
        T ans = Top();
        root1 = pop(root1);
        return ans;  
    }
    
	/// returns if the heap is empty
	bool Empty()
	{
		propagate();
		return (root1 == nullptr);
	}

    /// deletes a value from the heap
    void Erase(T val)
    {
        Node *nou = new Node(val);
        root2 = join(root2, nou);
    }
    
    /// joins the curent paring heap with oth. THIS WILL DESTROY OTH
    void Unite(PairingHeap & oth)
    { 
        root1 = join(root1, oth.root1);
        root2 = join(root2, oth.root2);
        oth.root1 = oth.root2 = 0;
    }

    /// creates a paring heap from a vector
    PairingHeap(vector <T> a = { }) : root1(nullptr), root2(nullptr)
    {
        for (auto i : a)
            Insert(i);
    }

    ~PairingHeap()
    {
        if (root1)
            delete root1;
        if (root2)
            delete root2;
    }
};

void manual_test()
{
    PairingHeap <int> ph;

    int op;
    cin >> op;

    cout << "Available:\nInsert\nTop\nErase\n";

    while (op --> 0) {
        string s;
        cin >> s;
        if (s[0] == 'I' || s[0] == 'i') {
            int val;
            cin >> val;
            ph.Insert(val);
        }
        else if (s[0] == 'T' || s[0] == 't') {
            cout << "Top = " << ph.Top() << '\n';
        }
        else if (s[0] == 'E' || s[0] == 'e') {
            int val;
            cin >> val;
            ph.Erase(val);
        }
    }
}


void tester()
{
    mt19937 rnd(time(0));
    while (true) {
        multiset <int> s;
        PairingHeap <int> ph;
        for (int _ = 0; _ < 1000; _++) {
            int op = rnd() % 3;
            if (op == 0) {
                if (rnd() % 10)
                    cerr << "?";
                /// find min
                if (!s.empty() && *s.begin() != ph.Top()) {
                    cerr << "WA\n";
                    exit(0);
                }
            }
            else if (op == 1) {
                if (rnd() % 10)
                    cerr << "+";
                int v = rnd() % 100;
                s.insert(v);
                ph.Insert(v);
            }
            else {
                if (rnd() % 10)
                    cerr << "-";
                if (s.empty())
                    continue;

                while (true) {
                    int x = rnd() % 100;
                    if (s.find(x) != s.end()) {
                        s.erase(s.find(x));
                        ph.Erase(x);
                        break;
                    }
                }
            }
        }
        cerr << "\nOK\n\n\n";
    }
}

int main()
{
    // tester();
    PairingHeap <int> ph;
    int N;
    cin >> N;

    while (N--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            ph.Insert(x);
        }
        else if (op == 2) {
            int x;
            cin >> x;
            ph.Erase(x);
        }
        else if (op == 3)
            cout << ph.Top() << '\n';
        else
            ph.Pop();
    }

    return 0;
}