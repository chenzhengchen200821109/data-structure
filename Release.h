#ifndef _RELEASE_H
#define _RELEASE_H

template<typename T>
struct Cleaner
{
    static void clean(T x)
    {
        return;
    }
};

template<typename T>
struct Cleaner<T*>
{
    static void clean(T* x) 
    {
        if (x)
            delete x;
    }
};


#endif
