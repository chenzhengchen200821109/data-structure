#include "MyStack.h"
#include <iostream>

int main()
{
    Stack<int> s;

    s.push(0);
    s.push(1);
    s.push(2);
    s.push(3);
    std::cout << s.pop() << std::endl;
    std::cout << s.pop() << std::endl;
    std::cout << "Stack size now is " << s.size() << std::endl;
    std::cout << s.pop() << std::endl;
    std::cout << s.pop() << std::endl;
    //std::cout << s.pop() << std::endl;
    
    return 0;
}
