#ifndef _MYDICTIONARY_H
#define _MYDICTIONARY_H

#include <utility>
#include <map>

template<typename K, typename V>
class Dictionary
{
    public:
        int size() const;
        bool put(K, V);
        V* get(K k) const;
        bool remove(K k);
    private:
        std::map<K, V> map_;
};

template<typename K, typename V>
int Dictionary<K, V>::size() const
{
    return map_.size();
}

template<typename K, typename V>
bool Dictionary<K, V>::put(K k, V v)
{
    std::pair<K, V> entry(k, v);
    typename std::pair<typename std::map<K, V>::iterator, bool> ret;
    ret = map_.insert(entry);
    return ret.second;
}

template<typename K, typename V>
V* Dictionary<K, V>::get(K k) const
{
    typename std::map<K, V>::iterator it;
    it = map_.find(k);
    if (it != map_.end())
        return &(it->second);
    return NULL;
}

template<typename K, typename V>
bool Dictionary<K, V>::remove(K k)
{
    typename std::map<K, V>::iterator it;
    it = map_.find(k);
    if (it != map_.end()) {
        map_.erase(it);
        return true;
    }
    return false;
}

#endif
