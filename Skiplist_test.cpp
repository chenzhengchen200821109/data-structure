#include <iostream>
#include "Skiplist.h"

int main()
{
    Skiplist<int, int>* sl = new Skiplist<int, int>;
    sl->put(1, 1);
    sl->put(2, 2);
    sl->put(3, 3);

    std::cout << *(sl->get(1)) << std::endl;
    return 0;
}
