#include <iostream>
#include "MyQueue.h"

int main()
{
    MyQueue<int> q;
    int a = 8;

    q.enqueue(10);
    q.enqueue(9);
    a = q.dequeue();
    std::cout << "a is now " << a << std::endl;
    std::cout << "size of queue is " << q.size() << std::endl;
    std::cout << "front is " << q.front() << std::endl;

    return 0;
}
