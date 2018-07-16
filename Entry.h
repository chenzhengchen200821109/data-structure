#ifndef _ENTRY_H
#define _ENTRY_H

template <typename Key, typename Value>
struct Entry 
{
    Key key;
    Value value;
    Entry(Key k, Value v) : key(k), value(v) {};
    Entry(Entry<Key, Value> const& e) : key(e.key), value(e.value) {};
    bool operator<(Entry<Key, Value> const& e) { return key < e.key; }
    bool operator>(Entry<Key, Value> const& e) { return key > e.key; }
    bool operator==(Entry<Key, Value> const& e) { return key == e.key; }
    bool operator!=(Entry<Key, Value> const& e) { return key != e.key; }
};

#endif
