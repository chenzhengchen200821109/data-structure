#include <iostream>
#include "BinTree.h"

int main()
{
    BinTree<int> bt;
    bt.insertAsRoot(1);
    BinNode<int>* pLeft = bt.insertAsLC(bt.root(), 2);
    BinNode<int>* pRight = bt.insertAsRC(bt.root(), 3);
    BinNode<int>* ppLeft = bt.insertAsLC(pLeft, 4);

    // insert a node which has already exist but has different data
    pLeft = bt.insertAsLC(bt.root(), 5);

    std::cout << pLeft->depth_ << std::endl;
    std::cout << pRight->depth_ << std::endl;
    std::cout << ppLeft->depth_ << std::endl;
    std::cout << pLeft->lChild_ << std::endl;
    std::cout << ppLeft << std::endl;

    // detach 
    BinTree<int>* pTree = bt.detach(pLeft);
    BinNode<int>* newRoot = pTree->root();
    std::cout << newRoot->depth_ << std::endl;
    std::cout << ppLeft->depth_ << std::endl;

    return 0;
}
