#ifndef _BSTREE_H
#define _BSTREE_H

/*
 * Balanced Sorted Tree
 */
#include <algorithm>
#include "BinTree.h"

template<typename T>
class BSTree 
{
    public:
        BSTree() tree_(new BinTree<T>), hot_(0) {};
        ~BSTree() { delete tree_; };
        BinNode<T>*& search(const T& e);
        BinNode<T>* insert(const T& e);
        bool remove(const T& e);
    private:
        BinNode<T>* rotateAt(BinNode<T>* x);
        BinNode<T>*& searchIn(BinNode<T>*& v, const T& e, BinNode<T>*& hot);
        BinNode<T>* connect34(BinNode<T>* a, BinNode<T>* b, BinNode<T>* c,
                BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2, BinNode<T>* T3);
        BinNode<T>* removeAt(BinNode<T>*& v, BinNode<T>*& hot);
        BinTree<T>* tree_;
        BinNode<T>* hot_;
};

// return NULL when failed otherwise the target node if found one
template<typename T>
BinNode<T>*& BSTree<T>::searchIn(BinNode<T>*& v, const T& e, BinNode<T>*& hot)
{
    if (!v || (v->data == e))
        return v;
    hot = v;
    return searchIn(((e < v->data) ? v->lChild_ : v->rChild_), e, hot);
}

template<typename T>
BinNode<T>*& BSTree<T>::search(const T& e)
{
    return searchIn(tree_.root_, e, hot_ = NULL);
}

template<typename T>
BinNode<T>* BSTree<T>::insert(const T& e)
{
    BinNode<T>*& x = tree_->search(e);
    // already in the tree
    if (x)
        return x;
    size_++;
    tree_->updateHeightAbove(x);
    return x;
}

template<typename T>
bool BSTree<T>::remove(const T& e)
{
    BinNode<T>*& x = tree_->search(e);
    if (!x) return false;
    removeAt(x, hot_);
    size_--;
    updateHeightAbove(hot_);
    return true;
}

template<typename T>
BinNode<T>* BSTree<T>::connect34(BinNode<T>* a, BinNode<T>* b, BinNode<T>* c,
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

template<typename T>
BinNode<T>* BST<T>::rotateAt(BinNode<T>* v)
{
    BinNode<T>* p = v->parent_;
    BinNode<T>* g = p->parent_;
    if (isLChild(*p)) { /* zig */
        if (isLChild(*v)) { /* zig-zig */
            p->parent_ = g->parent_;
            return connect34(v, p, g, v->lChild_, v->rChild_, p->rChild_, g->rChild_);
        } else { /* zig-zag */
            v->parent_ = g->parent_;
            return connect34(p, v, g, p->lChild_, v->lChild_, v->rChild_, g->rChild_);
        }
    } else { /* zag */
        if (isRChild(*v)) { /* zag-zig */
            p->parent_ = g->parent_;
            return connect34(g, p, v, g->lChild_, p->lChild_, v->lChild_, v->rChild_);
        } else { /* zag-zig */
            v->parent_ = g->parent_;
            return connect34(g, v, p, g->lChild_, v->lChild_, v->rChild_, p->rChild_);
        }
    
    }
}

template<typename T>
BinNode<T>* removeAt(BinNode<T>*& v, BinNode<T>*& hot)
{
    BinNode<T>* w = v;
    BinNode<T>* succ = NULL;
    if (!hasLChild(*v))
        succ = v = v->rChild_;
    else if (!hasRChild(*v))
        succ = v = v->lChild_;
    else {
        w = w->succ();
        std::swap(v->data, w->data);
        BinNode<T>* u = w->parent_;
        ((u == v) ? u->rChild_ : u->lChild_) = succ = w->rChild_;
    }
    hot = w->parent_;
    if (succ)
        succ->parent_ = hot;
    delete w->data;
    delete w;
    return succ;
}

#endif
