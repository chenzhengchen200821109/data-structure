#ifndef _AVL_H
#define _AVL_H

#include "BSTree.h"

#define Balanced(x) (stature((x).lChild_) == stature((x).rChild_))
#define BalFac(x) (stature((x).lChild_) - stature((x).rChild_))
#define AVLBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))

template<typename T>
class AVLTree
{
    public:
        AVLTree() {};
        ~AVLTree() {};
        BinNode<T>* insert(const T& e);
        bool remove(const T& e);
        BinNode<T>*& search(const T& e);
    private:
        BinNode<T>* tree_;
        BinNode<T>* connect34(BinNode<T>* a, BinNode<T>* b, BinNode<T>* c, 
                BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2, BinNode<T>* T3);
};

template<typename T>
BinNode<T>* AVLTree<T>::connect34(BinNode<T>* a, BinNode<T>* b, BinNode<T>* c,
        BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2, BinNode<T>* T3)
{
    a->lChild_ = T0;
    if (T0) T0->parent_ = a;
    a->rChild_ = T1;
    if (T1) T1->parent_ = a;
    updateHeight(a);
    c->lChild_ = T2;
    if (T2) T2->parent_ = c;
    c->rChild_ = T3;
    if (T3) T3->parent_ = c;
    updateHeight(c);
    b->lChild_ = a;
    a->parent_ = b;
    b->rChild_ = c;
    c->parent_ = b;
    updateHeight(b);
    return b;
}

#endif
