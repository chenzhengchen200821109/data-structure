#ifndef _DICTIONARY_H
#define _DICTIONARY_H

template<typename Key, typename Value>
class Dictionary
{
    public:
        virtual int size() = 0;
        virtual bool put(Key, Value) = 0;
        virtual Value* get(Key key) = 0;
        virtual bool remove(Key key) = 0;
};

#endif
