#include <iostream>
#include "HashTable.h"

int main()
{
    int* pvalue;
    HashTable<int, int> ht;
    ht.put(10, 10);
    ht.put(9, 9);
    pvalue = ht.get(10);
    std::cout << "value is " << *pvalue << std::endl;

    return 0;
}

