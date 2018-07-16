#include <iostream>
#include "MyQueue.h"

int main()
{
    Queue<int> q;
    int a = 8;

    q.enqueue(10);
    q.enqueue(9);
    a = q.dequeue();
    std::cout << "a is now " << a << std::endl;
    std::cout << "size of queue is " << q.size() << std::endl;

    return 0;
}
