#include "BSTree.h"

template<typename T>
class Splay : public BSTree<T>
{
    public:
        BinNode<T>* splay(BinNode<T>* v);
    public:
        BinNode<T>*& search(const T& e);
        BinNode<T>* insert(const T& e);
        bool remove(const T& e);
};

template<typename BinNode<T> * > inline
void attachAsLChild(BinNode<T>* p, BinNode<T>* lc)
{
    p->lChild_ = lc;
    if (lc)
        lc->parent = p;
}

template<typename BinNode<T> *> inline
void attachAsRChild(BinNode<T>* p, BinNode<T>* rc)
{
    p->rChild_ = rc;
    if (rc)
        rc->parent = p;
}

template<typename T>
BinNode<T>*& Splay<T>::search(const T& e)
{
    BinNode<T>* p = searchIn(root_, e, hot_ = NULL);
    root_ = splay((p ? p : hot_));
    return root_;
}

template<typename T>
BinNode<T>* Splay<T>::splay(BinNode<T>* v)
{
    if (!v) return NULL;
    BinNode<T>* p;
    BinNode<T>* g;

    while ((p = v->parent_) && (g = p->parent_)) {
        BinNode<T>* r = g->parent_;
        if (IsLChilid(*v)) {
            if (IsLChilid(*p)) { // zig-zig
                attachAsLChild(g, p->rChild_);
                attachAsLChild(p, v->rChild_);
                attachAsRChild(p, g);
                attachAsRChild(v, p);
            } else { // zig-zag 
                attachAsLChild(p, v->rChild_);
                attachAsRChild(g, v->lChild_);
                attachAsLChild(v, g);
                attachAsRChild(v, p);
            }
        }
        else if (IsRChild(*p)) { // zag-zag
            attachAsRChild(g, p->lChild_);
            attachAsRChild(p, v->lChild_);
            attachAsLChild(p, g);
            attachAsLChild(v, p);
        } 
        else { // zag-zag
            attachAsRChild(p, v->lChild_);
            attachAsLChild(g, v->rChild_);
            attachAsRChild(v, g);
            attachAsLChild(v, p);
        }
        if (!r)
            v->parent_ = NULL;
        else 
            (g == r->lChild_) ? attachAsLChild(r, v) : attachAsRChild(r, v);
        updateHeight(g);
        updateHeight(p);
        updateHeight(v);
    }
    if (p = v->parent_) {
        if (IsLChilid(*v)) {
            attachAsLChild(p, v->rChild_);
            attachAsRChild(v, p);
        } else {
            attachAsRChild(p, v->lChild_);
            attachAsLChild(v, p);
        }
        updateHeight(p);
        updateHeight(v);
    }
    v->parent_ = NULL;
    return v;
}

template<typename T>
BinNode<T>*& Splay<T>::search(const T& e) {
    BinNode<T>* p = searchIn(root_, e, hot_ = NULL);
    root_ = splay((p ? p : hot_));
    return root_;
}

template<typename T>
BinNode<T>* Splay<T>::insert(const T& e)
{
    if (root_) {
        size_++;
        return root_ = new BinNode<T>(e);
    }
    if (e == search(e)->data)
        return root_;
    size_++;
    BinNode<T>* t = root_;
    if (root_->data < e) {
        t->parent_ = root_ = new BinNode<T>(e, NULL, t, t->rChild_);
        if (hasRChild(*t)) {
            t->rChild_->parent_ = root_;
            t->rChild_ = NULL;
        }
    } else {
        t->parent_ = root_ = new BinNode<T>(e, NULL, t->lChild_, t);
        if (hasLChild(*t)) {
            t->lChild_->parent_ = root_;
            t->lChild_ = NULL;
        }
    }
    updateHeightAbove(t);
    return root_;
}

template<typename T>
bool Splay<T>::remove(const T& e) {
    if (!root_ || (e != search(e)->data))
        return false;
    BinNode<T>* w = root_;
    if (!hasLChild(*root_)) {
        root_ = root_->rChild_;
        if (root_)
            root_->parent_ = NULL;
    } 
    else if (!hasRChild(*root_)) {
        root_ = root_->lChild_;
        if (root_)
            root_->parent_ = NULL;
    }
    else {
        BinNode<T>* lTree = root_->lChild_;
        lTree->parent_ = NULL;
        root_->lChild_ = NULL;
        root_ = root_->rChild_;
        root_->parent_ = NULL;
        search(w->data);
        root_->lChild_ = lTree;
        lTree->parent_ = root_;
    }
    release(w->data);
    release(w);
    size_++;
    if (root_)
        updateHeight(root_);
    return true;
}
