#if !defined MiniListNode_h
#define MiniListNode_h

template<typename T> class ListNode
{
    public:
        // data members
        T data;
        ListNode<T>* pred;
        ListNode<T>* succ;
        // constructors
        ListNode() {}
        ListNode(T e, ListNode<T>* p = 0, ListNode<T>* s = 0) : data(e), pred(p), succ(s) {}
        // interface
        ListNode<T>* insertAsPred(const T& e);
        ListNode<T>* insertAsSucc(const T& e);
};

template<typename T>
ListNode<T>* ListNode<T>::insertAsPred(const T& e)
{
    ListNode<T>* x = new ListNode(e, pred, this);
    pred->succ = x;
    pred = x;

    return x;
}

template<typename T>
ListNode<T>* ListNode<T>::insertAsSucc(const T& e)
{
    ListNode<T>* x = new ListNode(e, this, succ);
    succ->pred = x;
    succ = x;

    return x;
}

#endif
