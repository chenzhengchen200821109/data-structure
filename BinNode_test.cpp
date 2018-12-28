#include <iostream>
#include "BinNode.h"

template<typename T>
struct print
{
    void operator()(T e)
    {
        std::cout << e << std::endl;
    }
};
int main()
{

    print<int> p;
    BinNode<int> root(1);

    BinNode<int>* pLeft = root.insertAsLC(2);
    BinNode<int>* pRight = root.insertAsRC(3);

    root.travLevel(p);

    delete pLeft;
    delete pRight;

    return 0;
}
