#include "Huffman.h"

int main(int argc, char* argv[])
{
    PFCForest* forest = new initForest();
    PFCTree* tree = generateTree(forest);
    PFCTable* table = generateTable(tree);
    for (int i = 1; i < argc; i++) {
        Bitmap codeString;
        int n = encode(table, codeString, argv[1]);
        decode(tree, codeString, n);
    }
    delete forest;
    delete tree;

    return 0;
}
