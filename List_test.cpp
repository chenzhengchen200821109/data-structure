#include <iostream>
#include "List.h"

void visit(int& n)
{
    std::cout << n << " ";
}

int main()
{
    List<int>* list = new List<int>;

    ListNode<int>* p0 = list->insertAsFirst(0);
    ListNode<int>* p1 = list->insertAsLast(9);
    list->traverse(&visit);
    std::cout << std::endl;

    list->insertAfter(p0, 8);
    list->insertAfter(p0, 7);
    list->insertAfter(p0, 6);
    ListNode<int>* p5 = list->insertAfter(p0, 5);
    list->insertBefore(p5, 1);
    list->insertBefore(p5, 2);
    list->insertBefore(p5, 3);
    list->insertBefore(p5, 4);

    list->traverse(&visit);
    std::cout << std::endl;

    return 0;
}
