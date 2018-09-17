#include "PQ_ComplHeap.h"
#include <iostream>

void printHeap(int& i)
{
    std::cout << i << std::endl;
}

int main()
{
    PQ_ComplHeap<int> *heap = new PQ_ComplHeap<int>;
    heap->insert(10);
    heap->insert(5);
    heap->insert(7);
    heap->insert(20);

    std::cout << "max element is " << heap->getMax() << std::endl;

    std::cout << heap->delMax() << std::endl;
    std::cout << heap->delMax() << std::endl;
    std::cout << heap->delMax() << std::endl;
    std::cout << heap->delMax() << std::endl;

    heap->insert(6);
    heap->insert(3);

    std::cout << "max element is " << heap->getMax() << std::endl;
    heap->traverse(printHeap);
    return 0;
}
