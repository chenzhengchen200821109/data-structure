#ifndef _LIST_H
#define _LIST_H

#include "ListNode.h"
#include <algorithm>

template<typename T>
class List
{
    private:
        int size_;
        ListNode<T>* header;
        ListNode<T>* trailer;
        void init();
        int clear();
        //void copyNodes(ListNode<T>*, int);
        //void merge(ListNode<T>&, int, List<T>&, ListNode<T>*, int);
        //void mergeSort(ListNode<T>&, int);
        //void selectionSort(ListNode<T>*, int);
        //void insertionSort(ListNode<T>*, int);
    public:
        List() { init(); }
        //List(List<T> const& list);
        //List(List<T> const& list, int r, int n);
        //List(ListNode<T>* p, int n);
        ~List();
        int size() const { return size_; }
        bool empty() const { return size_ <= 0; }
        ListNode<T>* operator[](int r) const;
        ListNode<T>* first() const { return header->succ; }
        ListNode<T>* last() const { return trailer->pred; }
        //bool isValid(ListNode<T>* p)
        //{ 
        //    return p && (trailer != p) && (header != p);
        //}
        //bool isValid(ListNode<T>* p, ListNode<T>* q, int r)
        //{
        //    while (0 < r) {
        //        if (p == (q = q->succ))
        //            return true;
        //    }
        //    return false;
        //}
        //bool isDisordered() const;
        //ListNode<T>* find(T const& e) const
        //{
        //    return find(e, size_, trailer);
        //}
        //ListNode<T>* find(T const& e, int n, ListNode<T>* p) const;
        //ListNode<T>* search(T const& e) const
        //{
        //    return search(e, size_, trailer);
        //}
        //ListNode<T>* search(T const& e, int n, ListNode<T>* p) const;
        //ListNode<T>* selectMax(ListNode<T>* p, int n) const;
        //ListNode<T>* selectMax() const 
        //{
        //    return selectMax(header->succ, size_);
        //}
        ListNode<T>* insertAsFirst(T const& e);
        ListNode<T>* insertAsLast(T const& e);
        ListNode<T>* insertBefore(ListNode<T>* p, T const& e);
        ListNode<T>* insertAfter(ListNode<T>* p, T const& e);
        T remove(ListNode<T>* p);
        void reverse();
        //void merge(List<T>& list)
        //{
        //    merge(first(), _size, list, list.first(), list.size());
        //}
        //void sort(ListNode<T>* p, int n);
        //void sort() { sort(first(), _size); }
        //int deduplicate();
        //int uniquify();
        void traverse(void (*)(T&));
        template<typename VST> void traverse(VST&);
}; // List

template<typename T>
void List<T>::init()
{
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer;
    header->pred = NULL;
    trailer->pred = header;
    trailer->succ = NULL;
    size_ = 0;
}

/*
template<typename T>
void List<T>::copyNodes(ListNode<T>* p, int n)
{
    init();
    while (n > 0) {
        insertAsLast(p->data);
        p = p->succ;
        n--;
    }
}

template<typename T>
List<T>::List(ListNode<T>* p, int n)
{
    copyNodes(p, n);
}

template<typename T>
List<T>::List(List<T> const& list, int r, int n)
{
    copyNodes(list[r], n);
}

template<typename T>
ListNode<T>* List<T>::operator[](int n) const
{
    assert(0 <= n && n < _size);
    ListNode<T>* p = first();
    while (n > 0) {
        p = p->succ;
        n--;
    }
    return p;
}

template<typename T>
ListNode<T>* List<T>::find(T const& e, int n, ListNode<T>* p) const
{
    assert(0 <= n && n < _size);
    while (n > 0) {
        if (e== (p = p->pred)->data)
            return p;
        n--;
    }
    return NULL;

}

template<typename T>
ListNode<T>* List<T>::search(T const& e, int n, ListNode<T>* p) const
{
    while (n >= 0) {
        if (((p = p->pred)->data) <= e)
            break;
        n--;
    }
    return p;
} */

template<typename T>
ListNode<T>* List<T>::insertAsFirst(T const& e)
{
    size_++;
    return header->insertAsSucc(e);
}

template<typename T>
ListNode<T>* List<T>::insertAsLast(T const& e)
{
    size_++;
    return trailer->insertAsPred(e);
}

template<typename T>
ListNode<T>* List<T>::insertBefore(ListNode<T>* p, T const& e)
{
    size_++;
    return p->insertAsPred(e);
}

template<typename T>
ListNode<T>* List<T>::insertAfter(ListNode<T>* p, T const& e)
{
    size_++;
    return p->insertAsSucc(e);
}

template<typename T>
T List<T>::remove(ListNode<T>* p)
{
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    size_ --;
    return e;
}

template<typename T>
List<T>::~List()
{
    clear();
    delete header;
    delete trailer;
}

template<typename T>
int List<T>::clear()
{
    int oldSize = size_;
    while (size_ > 0)
        remove(header->succ);
    return oldSize;
}

/*
template<typename T>
void List<T>::sort(ListNode<T>* p, int n)
{
    switch(rand() % 3) {
        case 1: insertionSort(p, n); break;
        case 2: selectionSort(p, n); break;
        default: mergeSort(p, n); break;
    }
}

template<typename T>
int List<T>::deduplicate()
{
    if (_size < 2)
        return 0;
    int oldSize = _size;
    ListNode<T>* p = header;
    int r = 0;
    while (trailer != (p = p->succ)) {
        ListNode<T>* q = find(p->data, r, p);
        q ? remove(q) : r++;
    }
    return oldSize - _size;
} */

/*
 * reverse a list
 */
template<typename T>
void List<T>::reverse()
{
    ListNode<T>* node = header;
    while (node)
    {
        ListNode<T>* Next = node->succ;
        ListNode<T>* Prev = node->pred;
        node->pred = Next;
        node->succ = Prev;
        node = Next;
    }
    std::swap(header, trailer);
}

template<typename T>
void List<T>::traverse(void (*visit)(T&))
{
    for (ListNode<T>* p = header->succ; p != trailer; p = p->succ)
        visit(p->data);
}

template<typename T> template<typename VST>
void List<T>::traverse(VST& visit)
{
    for (ListNode<T>* p = header->succ; p != trailer; p = p->succ)
        visit(p->data);
}

/*
template<typename T>
int List<T>::uniquify()
{
    if (_size < 2)
        return 0;
    int oldSize = _size;
    ListNode<T>* p, q;
    for (p = header, q = p->succ; trailer != q; p = q, q = q->succ) {
        if (p->data == q->data) {
            remove(q);
            q = p;
        }
    }
    return oldSize - _size;
} */

#endif
