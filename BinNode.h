#if !defined _BinNode_H
#define _BinNode_H

#include <cstdlib>
#include "MyQueue.h"

#define stature(p) ((p) ? (p)->height_ : -1)
//typedef enum { RB_RED, RB_BLACK } RBColor;

#define isRoot(x) (!((x).parent_))
#define isLChild(x) (!IsRoot(x) && (&(x) == (((x).parent_)->lChild_)))
#define isRChild(x) (!IsRoot(x) && (&(x) == (((x).parent_)->rChild_)))
#define hasParent(x) (!isRoot)
#define hasLChild(x) ((x).lChild_)
#define hasRChild(x) ((x).rChild_)
#define hasChild(x) (hasLChild(x) || hasRChild(x))
#define hasBothChild(x) (hasLChild(x) && hasRChild(x))
#define isLeaf(x) (!hasChild(x))

// binary tree node
template<typename T>
class BinNode
{
    public:
        BinNode() : parent_(0), lChild_(0), rChild_(0), height_(0) {}
        BinNode(T e, BinNode<T>* p = 0, BinNode<T>* lc = 0, BinNode<T>* rc = 0, int h = 0) : data_(e), parent_(p), lChild_(lc), rChild_(rc), height_(h) {}
        // insert a node as current node's left child
        BinNode<T>* insertAsLC(T const& e);
        // insert a node as current node's right child
        BinNode<T>* insertAsRC(T const& e);
        BinNode<T>* succ();
        // level-order traversal
        template<typename VST> void travLevel(VST&);
        // traverse binary tree using recursive algorithm
        template<typename VST> void traverse(VST&);
        // preorder traversal
        template<typename VST> void travPre_R(VST&);
        // inorder traversal
        template<typename VST> void travIn_R(VST&);
        // postorder traversal
        template<typename VST> void travPost_R(VST&);
        bool operator<(BinNode<T> const& bn) { return data_ < bn.data_; }
        bool operator==(BinNode<T> const& bn) { return data_ == bn.data_; }
        T data_;
        BinNode<T>* parent_;
        BinNode<T>* lChild_;
        BinNode<T>* rChild_;
        int height_;
        //int npl;
        //RBColor color; // used for red-black tree
};

template<typename T>
BinNode<T>* BinNode<T>::insertAsLC(T const& e)
{
    return lChild_ = new BinNode<T>(e, this);
}

template<typename T>
BinNode<T>* BinNode<T>::insertAsRC(T const& e)
{
    return rChild_ = new BinNode<T>(e, this);
}

/*
 * succ() defines a logical linear relationship between nodes.
 */
template<typename T>
BinNode<T>* BinNode<T>::succ()
{
    BinNode<T>* s = this;
    if (rChild_) {
        s = rChild_;
        while (hasLChild(*s))
            s = s->lChild_;
    } else {
        while (isLChild(*s))
            s = s->parent_;
        s = s->parent_;
    }
    return s;
}

template<typename T> template<typename VST>
void BinNode<T>::traverse(VST& visit)
{
    switch(std::rand() % 3) {
        case 1: travPre_R(visit); break;
        case 2: travIn_R(visit); break;
        default: travPost_R(visit); break;
    }
}

template<typename T> template<typename VST>
void BinNode<T>::travPre_R(VST& visit)
{
    travPre(this, visit);
}

template<typename T, typename VST>
static void travPre(BinNode<T>* x, VST& visit)
{
    if (!x)
        return;
    visit(x->data);
    travPre(x->lChild_, visit);
    travPre(x->rChild_, visit);
}

template<typename T> template<typename VST>
void BinNode<T>::travIn_R(VST& visit)
{
    travIn(this, visit);
}

template<typename T, typename VST>
static void travIn(BinNode<T>* x, VST& visit)
{
    if (!x)
        return;
    travIn(x->lChild_, visit);
    visit(x->data_);
    travIn(x->rChild_, visit);
}

template<typename T> template<typename VST>
void BinNode<T>::travPost_R(VST& visit)
{
    travPost(this, visit);
}

template<typename T, typename VST>
static void travPost(BinNode<T>* x, VST& visit)
{
    if (!x)
        return;
    travPost_R(x->lChild_, visit);
    travPost_R(x->rChild_, visit);
    visit(x->data_);
}

template<typename T> template<typename VST>
void BinNode<T>::travLevel(VST& visit)
{
    Queue<BinNode<T>* > Q;
    Q.enqueue(this);
    while (!Q.empty()) {
        BinNode<T>* x = Q.dequeue();
        visit(x->data_);
        if (hasLChild(*x))
            Q.enqueue(x->lChild_);
        if (hasRChild(*x))
            Q.enqueue(x->rChild_);
    }
}

#endif
