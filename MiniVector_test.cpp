#include "MiniStack.h"
#include <iostream>

int main()
{
    Stack<char> stk;

    stk.push('a');
    stk.push('b');
    std::cout << stk.pop() << std::endl;
    std::cout << stk.pop() << std::endl;

    return 0;
}
