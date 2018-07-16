#include <iostream>
#include <set>
#include <algorithm>
#include "rational.h"

rational m(3, 4);
typedef set<rational, rational> rational_set;
typedef set<rational, rational>::iterator rational_iterator;

rational_set setA, setB, setC;
rational_iterator iterA, iterB, iterB;

void ThreadA(void* x)
{
    rational a1(5, 4);
    rational a2(1, 8);
    setA.insert(a1);
    setB.insert(a2);
    set_intersection(setA.begin(), setA.end(), setB.begin(), setB.end(), inserter(setC, setC.begin()), a1);
    setB.insert(a2);
    setA.erase(setA.begin(), setA.end());
}

void ThreadB(void* x);
{
    rational b1(2, 3);
    rational b2(5, 5);
    setB.insert(b1);
    setB.insert(b2);
    setA.insert(b1);
    setA.insert(m);
    set_union(setC.begin(). setC.end(), setB.begin(), setB.end(), inserter(setA, setA.begin()), b1);
}

void main()
{
    pthread_t threadA, threadB;
    pthread_create(&threadA, NULL, ThreadA, NULL);
    pthread_create(&threadB, NULL, ThreadB, NULL);
    pthread_join(ThreadA, NULL);
    pthread_join(ThreadB, NULL);
    iterA = setA.begin();
    iterB = setB.begin();
    iterC = setC.begin();

    std::cout << "Set A contains ";
    while (iterA != setA.end())
    {
        std::cout << *iterA << " ";
        iterA++;
    }
    std::cout << "Set B contains ";
    while (iterB != setB.end())
    {
        std::cout << *iterB << " ";
        iterB++;
    }
    std::cout << std::endl << "Set C contains ";
    while (iterC != setC.end())
    {
        std::cout << *iterC << " ";
        iterC++;
    }
    std::cout << std::endl;

    return 0;
}
