#ifndef _LISTNODE_H
#define _LISTNODE_H

template<typename T>
struct ListNode
{
    T data;
    ListNode<T>* pred;
    ListNode<T>* succ;
    ListNode() {}
    ListNode(T e, ListNode<T>* p = NULL, ListNode<T>* s = NULL)
        : data(e), pred(p), succ(s) {}
    ListNode<T>* insertAsPred(T const& e);
    ListNode<T>* insertAsSucc(T const& e);
};

template<typename T>
ListNode<T>* ListNode<T>::insertAsPred(T const& e)
{
    ListNode<T>* p = new ListNode(e, pred, this);
    pred->succ = p;
    pred = p;
    return p;
}

template<typename T>
ListNode<T>* ListNode<T>::insertAsSucc(T const& e)
{
    ListNode<T>* p = new ListNode(e, this, succ);
    succ->pred = p;
    succ = p;
    return p;
}

#endif
