#ifndef _MYDEQUE_H
#define _MYDEQUE_H

#include <list>
#include <cassert>

template<typename T>
class Deque
{
    public:
        int size() const;
        bool empty() const;
        void insertFront(T const& e);
        void insertRear(T const& e);
        T removeFront();
        T removeRear();
        T& front() const;
        T& rear() const;
    private:
        std::list<T> list_;
};


#endif
