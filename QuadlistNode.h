#ifndef _QUADLISTNODE_H
#define _QUADLISTNODE_H

#include "Entry.h"

template<typename T>
class QuadlistNode 
{
    public:
        T entry_;
        QuadlistNode<T>* pred;
        QuadlistNode<T>* succ;
        QuadlistNode<T>* above;
        QuadlistNode<T>* below;
        QuadlistNode() {}
        // prev, succ, above, below
        QuadlistNode(T e, QuadlistNode<T>* p = NULL, QuadlistNode<T>* s = NULL,
                QuadlistNode<T>* a = NULL, QuadlistNode<T>* b = NULL)
                : entry_(e), pred(p), succ(s), above(a), below(b) {}
        QuadlistNode<T>* insertAsSuccAbove(T const& e, QuadlistNode<T>* b = NULL);
};

template<typename T>
QuadlistNode<T>* QuadlistNode<T>::insertAsSuccAbove(T const& e, QuadlistNode<T>* b)
{
    QuadlistNode<T>* x = new QuadlistNode<T>(e, this, succ, NULL, b);
    succ->pred = x; // horizontal direction
    succ = x; // horizontal direction
    if (b) // vertical direction
        b->above = x;
    return x;
}

#endif

