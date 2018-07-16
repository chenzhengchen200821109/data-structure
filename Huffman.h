#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include "BinNode.h"
#include "BinTree.h"
typedef BinTree<char> PFCTree;

#include "Vector.h"
typedef Vector<PFCTree*> PFCForest;

#include "Bitmap.h"
#include "Skiplist.h"
typedef Skiplist<char, char*> PFCTable;

#define NCHAR (0X80 - 0X20)

PFCForest* initForest()
{
    // forest
    PFCForest* forest = new PFCForest;
    for (int i = 0; i < NCHAR; i++) {
        forest->insert(i, new PFCTree());
        (*forest)[i]->insertAsRoot(0x20 + i);
    }
    return forest;
}

PFCTree* generateTree(PFCForest* forest)
{
    srand((unsigned int)time(NULL));
    while (forest->size() > 1) {
        PFCTree* s = new PFCTree;
        s->insertAsRoot('^');
        int r1 = rand() % forest->size();
        s->attachAsLC(s->root(), (*forest)[r1]);
        forest->remove(r1);
        int r2 = rand() % forest->size();
        s->attachAsRC(s->root(), (*forest)[r2]);
        forest->remove(r2);
        forest->insert(forest->size(), s);
    }
    return (*forest)[0];
}

void generateCT(Bitmap* code, int length, PFCTable* table, BinNode<char>* v)
{
    if (isLeaf(*v)) {
        table->put(v->data, code->bits2string(length));
        return;
    }
    if (hasLChild(*v)) {
        code->clear(length);
        generateCT(code, length + 1, table, v->lChild_);
    }
    if (hasRChild(*v)) {
        code->set(length);
        generateCT(code, length + 1, table, v->rChild_);
    }
}

PFCTable* generateTable(PFCTree* tree)
{
    PFCTable* table = new PFCTable;
    Bitmap* code = new Bitmap;
    generateCT(code, 0, table, tree->root());
    delete code;
    return table;
}

int encode(PFCTable* table, Bitmap& codeString, char* s)
{
    int n = 0;
    for (size_t m = strlen(s), i = 0; i < m; i++) {
        char** pCharCode = table->get(s[i]);
        if (!pCharCode) pCharCode = table->get(s[i] + 'A' - 'a');
        if (!pCharCode) pCharCode = table->get(' ');
        printf("%s", *pCharCode);
        for (size_t m = strlen(*pCharCode), j = 0; j < m; j++)
            '1' == *(*pCharCode + j) ? codeString.set(n++) : codeString.clear(n++);
    }
    return n;
}

void decode(PFCTree* tree, Bitmap& code, int n)
{
    BinNode<char>* x = tree->root();
    for (int i = 0; i < n; i++) {
        x = code.test(i) ? x->rChild_ : x->lChild_;
        if (isLeaf(*x)) {
            printf("%c", x->data);
            x = tree->root();
        }
    }
}

#endif
