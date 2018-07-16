#ifndef _BINTREE_H
#define _BINTREE_H

/*
 * Binary Tree
 */
#include <algorithm>
#include "BinNode.h"

template<typename T>
class BinTree
{
    public:
        BinTree() : size_(0), root_(NULL) {}
        ~BinTree() { if (size_ > 0) remove(root_); }
        int size() const { return size_; }
        BinNode<T>* root() const { return root_; }
        BinNode<T>* insertAsRoot(T const& e);
        BinNode<T>* insertAsLC(BinNode<T>* x, T const& e);
        BinNode<T>* insertAsRC(BinNode<T>* x, T const& e);
        BinNode<T>* attachAsLC(BinNode<T>* x, BinTree<T>* &t);
        BinNode<T>* attachAsRC(BinNode<T>* x, BinTree<T>* &t);
        int remove(BinNode<T>* x);
        BinTree<T>* secede(BinNode<T>* x);
        int updateHeight(BinNode<T>* x);
        void updateHeightAbove(BinNode<T>* x);
        //template<typename VST> void travLevel(VST& visit)
        //{
        //    if (root_) root_->travLevel(visit);
        //}
        template<typename VST> void travPre(VST& visit)
        {
            if (root_) root_->travPre_R(visit);
        }
        template<typename VST> void travIn(VST& visit)
        {
            if (root_) root_->travIn_R(visit);
        }
        template<typename VST> void travPost(VST& visit)
        {
            if (root_) root_->travPost_R(visit);
        }
        //bool operator<(BinTree<T> const& t)
        //{
        //    return root_ && t.root_ && lt(root_, t.root_);
        //}
        //bool operator==(BinTree<T> const& t)
        //{
        //    return root_ && t.root_ && (root_ == t.root_);
        //}
    private:
        int size_;
        BinNode<T>* root_;
        int removeAt(BinNode<T>* x);
};

template<typename T>
int BinTree<T>::updateHeight(BinNode<T>* x)
{
    return x->height_ = 1 + std::max(stature(x->lChild_), stature(x->rChild_));
}

template<typename T>
void BinTree<T>::updateHeightAbove(BinNode<T>* x)
{
    while (x) {
        updateHeight(x);
        x = x->parent_;
    }
}

template<typename T>
BinNode<T>* BinTree<T>::insertAsRoot(T const& e)
{
    size_ = 1;
    return root_ = new BinNode<T>(e);
}

template<typename T>
BinNode<T>* BinTree<T>::insertAsLC(BinNode<T>* x, T const& e)
{
    size_++;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lChild_;
}

template<typename T>
BinNode<T>* BinTree<T>::attachAsLC(BinNode<T>* x, BinTree<T>* &s)
{
    if (x->lChild_ = s->root_)
        x->lChild_->parent_ = x;
    size_ += s->size_;
    updateHeightAbove(x);
    s->root_ = NULL;
    s->size_ = 0;
    delete s;
    s = NULL;
    return x;
}

template<typename T>
BinNode<T>* BinTree<T>::attachAsRC(BinNode<T>* x, BinTree<T>* &s)
{
    if (x->rChild_ = s->root_)
        x->rChild_->parent_ = x;
    size_ += s->size_;
    updateHeightAbove(x);
    s->root_ = NULL; 
    s->size_ = 0;
    delete s;
    s = NULL;
    return x;
}

template<typename T>
int BinTree<T>::remove(BinNode<T>* x)
{
    fromParentTo(*x) = NULL;
    updateHeightAbove(x->parent_);
    int n = removeAt(x);
    size_ -= n;
    return n;
}

template<typename T>
int BinTree<T>::removeAt(BinNode<T>* x)
{
    if (!x)
        return 0;
    int n = 1 + removeAt(x->lChild_) + remove(x->rChild_);
    delete x->data_;
    delete x;
    return n;
}

/*
 * 
 */
template<typename T>
BinTree<T>* BinTree<T>::secede(BinNode<T>* x)
{
    fromParentTo(*x) = NULL;
    updateHeightAbove(x->parent_);
    BinTree<T>* s = new BinTree<T>;
    s->root_ = x;
    x->parent_ = NULL;
    s->size_ = x->size();
    size_ -= s->size_;
    return s;
}

#endif
