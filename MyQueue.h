#ifndef _MYQUEUE_H
#define _MYQUEUE_H

#include "MyList.h"

template<typename T>
class MyQueue: public MyList<T>
{
    public:
        int size() const;
        bool empty() const;
        void enqueue(T const& e);
        T dequeue();
        T& front() const;
};

template<typename T>
int MyQueue<T>::size() const
{
    return MyList<T>::size();
}

template<typename T>
bool MyQueue<T>::empty() const
{
    return MyList<T>::empty();
}

template<typename T>
void MyQueue<T>::enqueue(T const& e)
{
    MyList<T>::insertAsLast(e);
}

template<typename T>
T MyQueue<T>::dequeue()
{
    MyList<T>::remove(MyList<T>::firstNode());
}

template<typename T>
T& MyQueue<T>::front() const
{
    return MyList<T>::firstNode()->data;
}

#endif
