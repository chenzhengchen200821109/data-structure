#ifndef _MYQUEUE_H
#define _MYQUEUE_H

#include <list>
#include <cassert>

template<typename T>
class Queue
{
    public:
        int size() const;
        bool empty() const;
        void enqueue(T const& e);
        T dequeue();
        T& front() const;
    private:
        std::list<T> list_;
};

template<typename T>
int Queue<T>::size() const
{
    return list_.size();
}

template<typename T>
bool Queue<T>::empty() const
{
    return list_.empty();
}

template<typename T>
void Queue<T>::enqueue(T const& e)
{
    list_.push_back(e);
}

template<typename T>
T Queue<T>::dequeue()
{
    assert(!empty()); // Should we really use assert here ???
    T e = list_.front();
    list_.pop_front();
    return e;
}

template<typename T>
T& Queue<T>::front() const
{
    return list_.front();
}

#endif
