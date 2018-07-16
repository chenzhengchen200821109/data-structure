#include "PQ_ComplHeap.h"
#include <iostream>

int main()
{
    PQ_ComplHeap<int> *heap = new PQ_ComplHeap<int>;
    heap->insert(10);
    heap->insert(5);

    std::cout << heap->getMax() << std::endl;

    return 0;
}
