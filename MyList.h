#if !defined MYLIST_H
#define MYLIST_H

#include "MyListNode.h"

template<typename T> class MyList
{
    private:
        int _size;
        ListNode<T>* header;
        ListNode<T>* trailer;
    protected:
        void init();
        int clear();
        void copyNodes(ListNode<T>* node, int n);
    public:
        // constructor
        MyList() { init(); }
        MyList(const MyList<T>& list);
        MyList(const MyList<T>& list, int index, int n);
        MyList(ListNode<T>* node, int n);
        // destructor
        ~MyList();
        // only readable interfaces
        int size() const { return _size; }
        bool empty() const { return _size <= 0; }
        ListNode<T>* operator[](int index) const;
        ListNode<T>* firstNode() const { return header->succ; }
        ListNode<T>* lastNode() const { return trailer->pred; }
        bool valid(ListNode<T>* node) const { return node && (node != trailer) && (node != header); }
        // search interfaces
        ListNode<T>* find(const T& e) const { return find(e, _size, trailer); }
        ListNode<T>* find(const T& e, int n, ListNode<T>* node) const;
        // writable interfaces
        ListNode<T>* insertAsFirst(const T& e);
        ListNode<T>* insertAsLast(const T& e);
        ListNode<T>* insertBefore(ListNode<T>* node, const T& e);
        ListNode<T>* insertAfter(ListNode<T>* node, const T& e);
        T remove(ListNode<T>* node);
};

template<typename T>
void MyList<T>::init()
{
    header = new ListNode<T>;
    trailer = new ListNode<T>;

    header->succ = trailer;
    header->pred = 0;
    trailer->pred = header;
    trailer->succ = 0;
    _size = 0;
}

template<typename T>
int MyList<T>::clear()
{
    int oldSize = _size;
    while (_size > 0)
        remove(header->succ);

    return oldSize;
}

template<typename T>
void MyList<T>::copyNodes(ListNode<T>* node, int n)
{
    init();
    while (n--) {
        insertAsLast(node->data);
        node = node->succ;
    }
}

template<typename T>
MyList<T>::MyList(const MyList<T>& list)
{
    copyNodes(list.firstNode(), list._size);
}

template<typename T>
MyList<T>::MyList(const MyList<T>& list, int index, int n) 
{
    copyNodes(list[index], n);
}

template<typename T>
MyList<T>::MyList(ListNode<T>* node, int n)
{
    copyNodes(node, n);
}

template<typename T>
MyList<T>::~MyList()
{
    clear();
    delete header;
    delete trailer;
}

template<typename T>
ListNode<T>* MyList<T>::operator[](int index) const
{
    //assert: 0 <= index < _size
    ListNode<T>* p = firstNode();
    while (index > 0) {
        p = p->succ;
        index--;
    }
}

template<typename T>
ListNode<T>* MyList<T>::find(const T& e, int n, ListNode<T>* node) const
{
    while (n-- > 0)
        if (e == (node = node->pred)->data)
            return node;
    return 0;
}

template<typename T>
ListNode<T>* MyList<T>::insertAsFirst(const T& e)
{
    _size++;
    return header->insertAsSucc(e);
}

template<typename T>
ListNode<T>* MyList<T>::insertAsLast(const T& e)
{
    _size++;
    return trailer->insertAsPred(e);
}

template<typename T>
ListNode<T>* MyList<T>::insertBefore(ListNode<T>* node, const T& e)
{
    _size++;
    return node->insertAsPred(e);
}

template<typename T>
ListNode<T>* MyList<T>::insertAfter(ListNode<T>* node, const T& e)
{
    _size++;
    return node->insertAsSucc(e);
}

// node must be valid
template<typename T>
T MyList<T>::remove(ListNode<T>* node)
{
    T e = node->data;
    node->pred->succ = node->succ;
    node->succ->pred = node->pred;
    delete node;
    _size--;

    return e;
}

#endif
