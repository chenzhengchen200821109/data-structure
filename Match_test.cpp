#include <iostream>
#include <cstring>
#include "Match.h"

int main()
{
    char* p = "ABCABCDAAB";
    size_t len = strlen(p);
    int* Next = buildNext(p);
    for (int i = 0; i < len; i++) {
        std::cout << p[i];
    }
    std::cout << std::endl;
    for (int i = 0; i < len; i++) {
        std::cout << Next[i];
    }
    std::cout << std::endl;

    return 0;
}
