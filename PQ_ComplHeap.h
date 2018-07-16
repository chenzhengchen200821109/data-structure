#ifndef _PQ_COMPLHEAP_H
#define _PQ_COMPLHEAP_H

#include "PQ.h"
#include <vector>
#include <algorithm>

template<typename T>
static bool lt(T A, T B)
{
    return (A < B) ? true : false;
}

template<typename T>
static int percolateUp(std::vector<T>* A, int i)
{
    while (ParentValid(i)) {
        int j = Parent(i);
        if (lt(Node(*A, i), Node(*A, j)))
            break;
        std::swap(Node(*A, i), Node(*A, j));
        i = j;
    }
    return i;
}

template<typename T>
static int percolateDown(std::vector<T>* A, int n, int i)
{
    int j;
    while (i != (j = ProperParent(*A, n, i))) {
        std::swap(Node(*A, i), Node(*A, j));
        i = j;
    }
    return i;
}

template<typename T>
static int percolateDown(T* A, int n, int i)
{
    int j;
    while (i != (j = ProperParent(A, n, i))) {
        swap(Node(A, i), Node(A, j));
        i = j;
    }
    return i;
}

template<typename T>
static T* heapify(T* e, int lo, int hi)
{
    for (int i = LastInternal(hi - lo); InHeap(hi - lo, i); i--)
        percolateDown(e + lo, hi - lo, i);
    return e;
}

template<typename T>
static T* heapify(T* e, int n)
{
    return heapify(e, 0, n);
}

template<typename T>
class PQ_ComplHeap : public PQ<T>
{
    private:
        std::vector<T>* heap;
    public:
        PQ_ComplHeap() { heap = new std::vector<T>; }
        PQ_ComplHeap(T* e, int n)
        {
            heap = new std::vector<T>(heapify(e, n), n);
        }
        ~PQ_ComplHeap() { delete heap; }
        int size() { return heap->size(); }
        bool empty() const { return heap->empty(); }
        void insert(T);
        T getMax();
        T delMax();
};

template<typename T>
T PQ_ComplHeap<T>::getMax()
{
    return heap->front();
}

template<typename T>
void PQ_ComplHeap<T>::insert(T e)
{
    heap->push_back(e);
    percolateUp(heap, size() - 1);
}

template<typename T>
T PQ_ComplHeap<T>::delMax()
{
    T maxElem = heap->front();
    (*heap)[0] = heap->back();
    heap->pop_back();
    percolateDown(heap, size(), 0);
    return maxElem;
}

#endif
