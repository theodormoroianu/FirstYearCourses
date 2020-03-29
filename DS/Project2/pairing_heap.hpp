#ifndef PAIRING_HEAP_
#define PAIRING_HEAP_


#include <vector>
#include <functional>
#include <stdexcept>

/**
 * Class T MUST have '<' ans '>' operators
 * 
 * first, third etc levels are min levels, rest are max levels
 * 
 * Pairing Heap is a max-heap structure.
 */


template <class T>
class PairingHeap
{
    struct Heap {
        T val;
        Heap *first_son, *next;
        
        Heap(T val) : val(val), first_son(0), next(0) { }
        ~Heap() {
            if (next)
                delete next;
            if (first_son)
                delete first_son;
        }
    };
    Heap* root;

    Heap* Join(Heap* a, Heap* b)
    {
        if (!a)
            return b;
        if (!b)
            return a;

        if (a->next || b->next)
            throw std::runtime_error("Tried to join two heaps that are still linked internally!");

        if (a->val >= b->val) {
            b->next = a->first_son;
            a->first_son = b;
            return a;
        }
        // else
        a->next = b->first_son;
        b->first_son = a;
        return b;
    }

    Heap* Pop(Heap* node)
    {
        Heap* ans = 0;
        for (Heap* a = node->first_son; a; ) {
            Heap *act = a, *urm = a->next;
            a = (urm ? urm->next : 0);
            act->next = 0;
            if (urm)
                urm->next = 0;
            ans = Join(ans, Join(act, urm));
        }

        node->first_son = 0;
        if (node->next)
            throw std::runtime_error("Internal error!");
        
        delete node;

        return ans;
    }
    
public:
    PairingHeap() : root(0) { }

    ~PairingHeap() {
        if (root)
            delete root;
    }

    void push(T val)
    {
        Heap* v = new Heap(val);
        root = Join(root, v);
    }

    T top()
    {
        if (!root)
            throw std::runtime_error("top operation requested on empty heap!");
        
        return root->val;
    }

    T pop()
    {
        if (!root)
            throw std::runtime_error("pop operation requested on empty heap!");
        
        T ans = root->val;
        root = Pop(root);

        return ans;
    }

    bool empty()
    {
        return (root == 0);
    }
};



#endif // PAIRING_HEAP_