#include <iostream>
#include "Quadlist.h"

void print(int& value)
{
    std::cout << value << std::endl;
}

int main()
{
    Quadlist<int>* list = new Quadlist<int>;
    QuadlistNode<int>* pFirst = list->insertAsFirst(1, NULL);
    
    list->insertAfterAbove(5, pFirst, NULL);
    list->insertAfterAbove(4, pFirst, NULL);
    list->insertAfterAbove(3, pFirst, NULL);
    list->insertAfterAbove(2, pFirst, NULL);
    list->insertAfterAbove(1, pFirst, NULL);
    
    std::cout << list->size() << std::endl;
    std::cout << "last node is " << list->last()->entry_ << std::endl;
    std::cout << "first node is " << list->first()->entry_ << std::endl;
    list->traverse(&print);

    return 0;
}
