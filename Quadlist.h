#ifndef _QUADLIST_H
#define _QUADLIST_H

#include "QuadlistNode.h"

template<typename T>
class Quadlist
{
    private:
        int size_;
        QuadlistNode<T>* header;
        QuadlistNode<T>* tailer;
        void init();
        int clear();
    public:
        Quadlist() { init(); }
        ~Quadlist() { clear(); delete header; delete tailer; }
        int size() const { return size_; }
        bool empty() const { return size_ <= 0; }
        QuadlistNode<T>* first() const { return header->succ; }
        QuadlistNode<T>* last() const { return tailer->pred; }
        bool valid(QuadlistNode<T>* p) { return ((p != header) && (p != tailer)); }
        T remove(QuadlistNode<T>* p);
        QuadlistNode<T>* insertAsFirst(T const& e, QuadlistNode<T>* b = NULL);
        QuadlistNode<T>* insertAfterAbove(T const& e, QuadlistNode<T>* p, QuadlistNode<T>* b = NULL);
        void traverse(void (*)(T&));
        template<typename VST> void traverse(VST&);
};

// initialization of Quadlist
template<typename T>
void Quadlist<T>::init()
{
    header = new QuadlistNode<T>;
    tailer = new QuadlistNode<T>;
    header->succ = tailer; // horizontal direction
    header->pred = NULL; // horizontal direction
    tailer->pred = header; // horizontal direction
    tailer->succ = NULL; // horizontal direction
    header->above = tailer->above = NULL; // vertical direction
    header->below = tailer->below = NULL; // vertical direction
    size_ = 0;
}

template<typename T>
int Quadlist<T>::clear()
{
    int oldSize = size_;
    while (size_ > 0)
        remove(header->succ);
    return oldSize;
}

template<typename T>
QuadlistNode<T>* Quadlist<T>::insertAfterAbove(T const& e, QuadlistNode<T>* p, QuadlistNode<T>* b) 
{
    size_++;
    return p->insertAsSuccAbove(e, b);
}

template<typename T>
QuadlistNode<T>* Quadlist<T>::insertAsFirst(T const& e, QuadlistNode<T>* b)
{
    size_++;
    return header->insertAsSuccAbove(e, b);
}

template<typename T>
T Quadlist<T>::remove(QuadlistNode<T>* p)
{
    T e = e->entry_;
    p->pred->succ = p->succ; // only horizontal direction
    p->succ->pred = p->pred; // only horizontal direction
    delete p;
    size_--;
    return e;
}

// traverse just like list
template<typename T>
void Quadlist<T>::traverse(void (*visit)(T&))
{
    for (QuadlistNode<T>* p = header->succ; p != tailer; p = p->succ)
        visit(p->entry_);
}

// traverse just like list
template<typename T> template<typename VST>
void Quadlist<T>::traverse(VST& visit)
{
    for (QuadlistNode<T>* p = header->succ; p != tailer; p = p->succ)
        visit(p->entry_);
}

#endif
