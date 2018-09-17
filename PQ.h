#ifndef _PQ_H
#define _PQ_H
#include <cstddef>

template <typename T> class PQ
{
    public:
        virtual size_t size() = 0;
        bool empty() const { return !size(); }
        virtual void insert(T) = 0;
        virtual T getMax() = 0;
        virtual T delMax() = 0;
};

// get value of a Node
#define Node(PQ, i) ((PQ)[i])
// validate Node i
#define InHeap(n, i) ((-1) < (i) && ((i) < (n)))
// index of parent of Node i
#define Parent(i) ((i-1) >> 1)
// last internal node (internal node is the node that have two children)
#define LastInternal(n) Parent(n-1)
// index of left child of Node i
#define LChild(i) (1 + ((i) << 1))
// index of right child of Node i
#define RChild(i) ((1 + (i)) << 1)
// Node i always has a parent node if i > 0
#define ParentValid(i) (i > 0)
#define LChildValid(n, i) InHeap(n, LChild(i))
#define RChildValid(n, i) InHeap(n, RChild(i))
#define Bigger(PQ, i, j) (lt(Node(PQ, i), Node(PQ, j)) ? j : i)
#define Smaller(PQ, i, j) (lt(Node(PQ, i), Node(PQ, j)) ? i : j)
// valid parent among Node i and its children
#define ProperParent(PQ, n, i) \
    (RChildValid(n, i) ? Bigger(PQ, Bigger(PQ, i, LChild(i)), RChild(i)) : \
    (LChildValid(n, i) ? Bigger(PQ, i, LChild(i)) : i))
// valid smaller child among Node i and its children
#define SmallerChild(PQ, n, i) \
    (RChildValid(n, i) ? Smaller(PQ, Smaller(PQ, i, LChild(i)), RChild(i)) : \
    (LChildValid(n, i) ? Smaller(PQ, i, LChild(i)) : i))

#endif
