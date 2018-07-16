#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <cstring>
#include "Entry.h"
#define PRIME 97

static size_t hashCode(char s[])
{
    int h = 0;
    for (size_t n = strlen(s), i = 0; i < n; i++) {
        h = (h << 5) | (h >> 27);
        h += (int) s[i];
    }
    return (size_t) h;
}

static size_t hashCode(int k)
{
    return (size_t) k;
}

static size_t hashCode(char c)
{
    return (size_t) c;
}

static size_t hashCode(long long v)
{
    return (size_t) ((v >> 32) + (int) v);
}

template<typename K, typename V>
class HashTable
{
    public:
        HashTable(int c = 10) : capacity_(c), size_(0)
        {
            ht = new Entry<K, V>* [PRIME];
            memset(ht, 0, sizeof(Entry<K, V>*) * PRIME);
        }
        ~HashTable();
        int size() const { return size_; }
        bool put(K, V);
        V* get(K k) const;
        bool remove(K k);
    private:
        int capacity_;
        int size_;
        Entry<K, V>** ht;
        int probe4Hit(const K& k) const;
        int probe4Free(const K& k) const;
};

template<typename K, typename V>
HashTable<K, V>::~HashTable()
{
    for (int i = 0; i < PRIME; i++) {
        if (ht[i])
            delete ht[i];
    }
    delete ht;
}

template<typename K, typename V>
V* HashTable<K, V>::get(K k) const
{
    int r = probe4Hit(k);
    return ht[r] ? &(ht[r]->value) : NULL;
}

template<typename K, typename V>
int HashTable<K, V>::probe4Hit(const K& k) const
{
    int r = hashCode(k) % PRIME;
    while (ht[r] && (k != ht[r]->key)) {
        r = (r + 1) % PRIME;
    }
    return r;
}

template<typename K, typename V>
bool HashTable<K, V>::remove(K k)
{
    int r = probe4Hit(k);
    if (!ht[r])
        return false;
    delete ht[r];
    ht[r] = NULL;
    size_--;
    return true;
}

template<typename K, typename V>
bool HashTable<K, V>::put(K k, V v)
{
    int r = probe4Hit(k);
    if (ht[r])
        return false;
    r = probe4Free(k);
    ht[r] = new Entry<K, V>(k, v);
    size_++;
    return true;
}

template<typename K, typename V>
int HashTable<K, V>::probe4Free(const K& k) const
{
    int r = hashCode(k) % PRIME;
    while (ht[r])
        r = (r + 1) % PRIME;
    return r;
}

#endif
