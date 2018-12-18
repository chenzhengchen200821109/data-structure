#include "BSTree.h"

template<typename T>
class Splay : public BSTree<T>
{
    private:
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
