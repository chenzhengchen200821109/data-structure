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

// keep swapping A[i] and A[Parent(i)] till A[i] <= A[Parent(i)]
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

// optimization for std::swap() 
template<typename T>
static int percolateUp_opt(std::vector<T>* A, int i)
{
    T larger;

    larger = Node(*A, i);
    while (ParentValid(i)) {
        int j = Parent(i);
        if (lt(larger, Node(*A, j)))
            break;
        else {
            Node(*A, i) = Node(*A, j);
            i = j;
        }
    }
    Node(*A, i) = larger;
    return i;
}

// 
template<typename T>
static int percolateDown(std::vector<T>* A, int n, int i)
{
    int j;

    while (i != (j = ProperParent(*A, n, i))) { // when i == j, no swap needed any more
        std::swap(Node(*A, i), Node(*A, j));
        i = j;
    }
    return i;
}

template<typename T>
static int percolateDown_opt(std::vector<T>* A, int n, int i)
{
    int j;
    T smaller;

    j = ProperParent(*A, n, i);
    if (i != j) {
        smaller = Node(*A, SmallerChild(*A, n, i));
        while (i != j) {
            Node(*A, i) = Node(*A, j);
            i = j;
            j = ProperParent(*A, n, i);
        }
        Node(*A, i) = smaller;
    }
    return i;
}

template<typename T>
static int percolateDown_opt(T* A, int n, int i)
{
    int j;
    T smaller;

    j = ProperParent(A, n, i);
    if (i != j) {
        smaller = Node(A, SmallerChild(A, n, i));
        while (i != j) {
            Node(A, i) = Node(A, j);
            i = j;
            j = ProperParent(A, n, i);
        }
        Node(A, i) = smaller;
    }
    return i;
}

// used for Floyd algorithm
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

// create a complete binary heap
template<typename T>
static T* heapify(T* e, int n)
{
    return heapify(e, 0, n);
}

// complete binary heap
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
        size_t size() { return heap->size(); }
        bool empty() const { return heap->empty(); }
        void insert(T);
        T getMax();
        T delMax();
        // for debug
        void traverse(void (*)(T&));
        // for debug only
};

template<typename T>
void PQ_ComplHeap<T>::traverse(void (*visit)(T&))
{
    size_t sz = size();
    for (size_t i = 0; i < sz; i++)
        visit(Node(*heap, i));
}

template<typename T>
T PQ_ComplHeap<T>::getMax()
{
    return heap->front();
}

template<typename T>
void PQ_ComplHeap<T>::insert(T e)
{
    heap->push_back(e);
    //percolateUp(heap, size() - 1);
    percolateUp_opt(heap, size() - 1);
}

template<typename T>
T PQ_ComplHeap<T>::delMax()
{
    T maxElem = heap->front();
    (*heap)[0] = heap->back();
    heap->pop_back();
    //percolateDown(heap, size(), 0);
    percolateDown_opt(heap, size(), 0);
    return maxElem;
}

#endif
