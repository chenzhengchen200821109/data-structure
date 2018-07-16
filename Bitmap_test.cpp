#include <iostream>
#include "Bitmap.h"

int main()
{
    Bitmap<16> bm;
    bm.set(10);
    std::cout << bm.test(10) << std::endl;

    return 0;
}

