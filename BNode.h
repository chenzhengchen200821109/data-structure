#ifndef _BTREE_H
#define _BTREE_H

#include "Vector.h"

template<typename T>
struct BTNode
{
    BTNode<T>* parent_;
    Vector<T> data_;
    Vector<BTNode<T>* > child_;
    BTNode() 
    {
        parent_ = NULL;
        child_.insert(0, NULL);
    }
    BTNode(T e, BTNode<T>* lc = NULL, BTNode<T>* rc = NULL)
    {
        parent_ = NULL;
        data_.insert(0, e);
        child_.insert(0, lc);
        child_.insert(1, rc);
        if (lc)
            lc->parent_ = this;
        if (rc)
            rc->parent_ = this;
    }
};

#endif
