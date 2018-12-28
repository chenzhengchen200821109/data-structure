#if !defined MyStack_h
#define MyStack_h

#include "MyVector.h"

template<typename T> 
class Stack : public Vector<T>
{
    public:
        void push(const T& e);
        T pop();
        T& top();
};

template<typename T>
void Stack<T>::push(const T& e)
{
    Stack<T>::insert(Stack<T>::size(), e);
}

template<typename T>
T Stack<T>::pop()
{
    return Stack<T>::remove(Stack<T>::size() - 1);
}

template<typename T>
T& Stack<T>::top()
{
    return (*this)[Stack<T>::size() - 1];
}

#endif
