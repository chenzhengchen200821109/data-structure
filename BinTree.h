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
        // must be called after instantiation of class BinTree
        BinNode<T>* insertAsRoot(T const& e);
        BinNode<T>* insertAsLC(BinNode<T>* x, T const& e);
        BinNode<T>* insertAsRC(BinNode<T>* x, T const& e);
        BinNode<T>* attachAsLC(BinNode<T>* x, BinTree<T>* &t);
        BinNode<T>* attachAsRC(BinNode<T>* x, BinTree<T>* &t);
        int remove(BinNode<T>* x);
        BinTree<T>* detach(BinNode<T>* x);
        // the following helper functions would better be private
        //int updateHeight(BinNode<T>* x);
        //void updateHeightAbove(BinNode<T>* x);
        //int updateDepth(BinNode<T>* x);
        //void updateDepthBelow(BinNode<T>* x);
        template<typename VST> void travLevel(VST& visit)
        {
            if (root_) root_->travLevel(visit);
        }
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
        int updateHeight(BinNode<T>* x);
        void updateHeightAbove(BinNode<T>* x);
        int updateDepthBelow(BinNode<T>* x, int d);
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
int BinTree<T>::updateDepthBelow(BinNode<T>* x, int d)
{
    if (!x) 
        return 0;
    x->depth_ -= d;
    updateDepthBelow(x->lChild_, d);
    updateDepthBelow(x->rChild_, d);
}

// insert a node as root
template<typename T>
BinNode<T>* BinTree<T>::insertAsRoot(T const& e)
{
    size_ = 1;
    return root_ = new BinNode<T>(e);
}

// FIXME: what if node x already has a left child
template<typename T>
BinNode<T>* BinTree<T>::insertAsLC(BinNode<T>* x, T const& e)
{
    BinNode<T>* newNode;
    BinNode<T>* oldNode;

    if (!hasLChild(*x)) { // x has right child or no child at all
        size_++;
        newNode = x->insertAsLC(e);
        updateHeightAbove(x);
        newNode->depth_ = x->depth_ + 1;
    } else { // x has both left and right child or only has right child
        oldNode = x->lChild_;
        newNode = x->insertAsLC(e);
        if (hasLChild(*oldNode)) {
            oldNode->lChild_->parent_ = newNode;
            newNode->lChild_ = oldNode->lChild_;
        }
        if (hasRChild(*oldNode)) {
            oldNode->rChild_->parent_ = newNode;
            newNode->rChild_ = oldNode->rChild_;
        }
        newNode->height_ = oldNode->height_;
        newNode->depth_ = oldNode->depth_;
        delete oldNode;
    }
    return newNode;
    //return x->lChild_;
}

// FIXME: what if node x already has a left child
template<typename T>
BinNode<T>* BinTree<T>::insertAsRC(BinNode<T>* x, T const& e)
{
    BinNode<T>* newNode;
    BinNode<T>* oldNode;

    if (!hasRChild(*x)) {
        size_++;
        newNode = x->insertAsRC(e);
        updateHeightAbove(x);
        newNode->depth_ = x->depth_ + 1;
    } else {
        oldNode = x->rChild_;
        newNode = x->insertAsRC(e);
        if (hasLChild(*oldNode)) {
            oldNode->lChild_->parent_ = newNode;
            newNode->lChild_ = oldNode->lChild_;
        }
        if (hasRChild(*oldNode)) {
            oldNode->rChild_->parent_ = newNode;
            newNode->rChild_ = oldNode->rChild_;
        }
        newNode->height_ = oldNode->height_;
        newNode->depth_ = oldNode->depth_;
        delete oldNode;
    }
    return newNode;
    //return x->lChild_;
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

// delete node x and its children
template<typename T>
int removeAt(BinNode<T>* x)
{
    if (!x)
        return 0;
    // recursive
    int n = 1 + removeAt(x->lChild_) + removeAt(x->rChild_);
    delete x;
    return n;
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

// detach a tree's subtree and return the new subtree 
template<typename T>
BinTree<T>* BinTree<T>::detach(BinNode<T>* x)
{
    int d = x->depth_; // d used for update depth of new subtree
    updateDepthBelow(x, d);
    fromParentTo(*x) = NULL;
    updateHeightAbove(x->parent_);
    BinTree<T>* newTree = new BinTree<T>;
    newTree->root_ = x;
    x->parent_ = NULL;
    //newTree->size_ = x->size();
    //size_ -= newTree->size_;
    return newTree;
}

#endif
