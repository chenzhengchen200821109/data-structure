#ifndef _PQ_H
#define _PQ_H

template <typename T> class PQ
{
    public:
        virtual int size() = 0;
        bool empty() const { return !size(); }
        virtual void insert(T) = 0;
        virtual T getMax() = 0;
        virtual T delMax() = 0;
};

#define Node(PQ, i) ((PQ)[i])
#define InHeap(n, i) ((-1) < (i) && ((i) < (n)))
#define Parent(i) ((i-1) >> 1)
#define LastInternal(n) Parent(n-1)
#define LChild(i) (1 + ((i) << 1))
#define RChild(i) ((1 + (i)) << 1)
#define ParentValid(i) (i > 0)
#define LChildValid(n, i) InHeap(n, LChild(i))
#define RChildValid(n, i) InHeap(n, RChild(i))
#define Bigger(PQ, i, j) (lt(Node(PQ, i), Node(PQ, j)) ? j : i)
#define ProperParent(PQ, n, i) \
    (RChildValid(n, i) ? Bigger(PQ, Bigger(PQ, i, LChild(i)), RChild(i)) : \
    (LChildValid(n, i) ? Bigger(PQ, i, LChild(i)) : i))

#endif
