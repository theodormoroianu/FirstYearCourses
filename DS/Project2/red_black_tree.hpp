#ifndef RED_BLACK_TREE_
#define RED_BLACK_TREE_

/**
 * Followed tutorial from [Here](https://www.cs.auckland.ac.nz/software/AlgAnim/red_black.html)
 */

template <class T>
class RedBlackTree
{
    struct Node
    {
        enum { red, black } color;
        Node *son[2], *father;
        T val;

        Node(T val) : color(red), son{ nullptr, nullptr }, father(nullptr), val(val) { }
        ~Node()
        {
            if (son[0])
                delete son[0];
            if (son[1])
                delete son[1];
        }
    } *root;

    void rotate(Node *nod, int dir)
    {
        /// TODO: 
    }

public:

    void insert(T val)
    {
        Node *nod = new Node(val);
        
        if (!root) {
            root = nod;
            nod->color = Node::black;
        }

        for (Node *act = root; ; ) {
            int where = (act->val >= val);
            if (!act->fii[where]) {
                act->fii[where] = nod;
                nod->father = act;
                break;
            }
            act = act->fii[where];
        }

        /// TODO:
    }

    bool find(T val)
    {
        for (Node *act = root; act; act = act->son[act->val > val])
            if (act->val == val)
                return true;
        return false;
    }

    void erase(T val)
    {
        /// TODO:
    }

    RedBlackTree()
    {
        root = nullptr;
    }
    ~RedBlackTree()
    {
        if (root)
            delete root;
    }
};

#endif // RED_BLACK_TREE_