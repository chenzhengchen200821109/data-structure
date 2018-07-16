#ifndef _SKIPLIST_H
#define _SKIPLIST_H

#include <cstdlib>
#include "List.h"
#include "Entry.h"
#include "Quadlist.h"
//#include "Dictionary.h"

template<typename K, typename V> // Key, value
class Skiplist
{
    public:
        Skiplist() : list_(0) { init(); }
        ~Skiplist() {}
        int size() const 
        {
            return empty() ? 0 : list_->last()->data->size();
        }
        bool empty() const
        {
            return list_->empty();
        }
        int level() const {
            return list_->size();
        }
        bool put(K, V);
        V* get(K k);
        bool remove(K k);
    private:
        List<Quadlist<Entry<K, V>* >* >* list_;
        bool skipSearch(ListNode<Quadlist<Entry<K, V>* >* >* &qlist, QuadlistNode<Entry<K, V>* >* &p, K const& key);
        void init() 
        {
            list_ = new List<Quadlist<Entry<K, V>* >* >;
        }
};

//template<typename Key, typename Value>
//class Skiplist : public Dictionary<Key, Value>, public List<Quadlist<Entry<Key, Value>* >* >
//{
//    protected:
//        bool skipSearch(ListNode<Quadlist<Entry<Key, Value>* >* >* &qlist, QuadlistNode<Entry<Key, Value>* >* &p, Key& key);
//    public:
//        int size()
//        {
//            return isEmpty() ? 0 : last()->data->size(); 
//        }
//        int level() { return List::size(); }
//        bool put(Key key, Value value);
//        V* get(Key key);
//        bool remove(Key key);
//};

// p will store the found node in the top level if return true
template<typename K, typename V>
bool Skiplist<K, V>::skipSearch(ListNode<Quadlist<Entry<K, V>* >* >* &qlist, QuadlistNode<Entry<K, V>* >* &p, K const& k)
{
    while (true) {
        while (p->succ && (p->entry_->key <= k))
            p = p->succ;
        p = p->pred;
        if (p->pred && (k == p->entry_->key)) return true;
        qlist = qlist->succ; // go to next level
        if (!qlist->succ) return false;
        p = (p->pred) ? p->below : qlist->data->first();
    }
}

template<typename K, typename V>
V* Skiplist<K, V>::get(K k)
{
    if (empty())
        return NULL;
    ListNode<Quadlist<Entry<K, V>* >* >* qlist = list_->first();
    QuadlistNode<Entry<K, V>* >* p = qlist->data->first();
    return skipSearch(qlist, p, k) ? &(p->entry_->value) : NULL;
}

template<typename K, typename V>
bool Skiplist<K, V>::put(K k, V v)
{
    Entry<K, V>* e = new Entry<K, V>(k, v);
    // insert the first entry
    if (empty())
        list_->insertAsFirst(new Quadlist<Entry<K, V>*>);
    ListNode<Quadlist<Entry<K, V>* >* >* qlist = list_->first(); // top level
    QuadlistNode<Entry<K, V>* >* p = qlist->data->first(); // first node in the top level
    if (skipSearch(qlist, p, k)) { // found
        //delete p->entry_;
        //p->entry_ = e; // update entry
        //while (p->below) {
        //    p = p->below;
        //    delete p->entry_;
        //    p->entry_ = e;
        //}
        do {
            delete p->entry_;
            p->entry_ = e;
        } while (p = p->below);
        return true;
    }
    qlist = list_->last();
    QuadlistNode<Entry<K, V>* >* b = qlist->data->insertAfterAbove(e, p, NULL);
    while (rand() % 2) {
        while (qlist->data->valid(p) && !p->above)
            p = p->pred;
        if (!qlist->data->valid(p)) {
            if (qlist == list_->first())
                list_->insertAsFirst(new Quadlist<Entry<K, V>* >);
            p = qlist->pred->data->first()->pred;
        } else 
            p = p->above;
        qlist = qlist->pred;
        b = qlist->data->insertAfterAbove(e, p, b);
    }
    return true;
}

template<typename K, typename V>
bool Skiplist<K, V>::remove(K k)
{
    if (empty())
        return false;
    ListNode<Quadlist<Entry<K, V>* >* >* qlist = list_->first();
    QuadlistNode<Entry<K, V>* >* p = qlist->data->first();
    if (!skipSearch(qlist, p, k)) // if not found
        return false;
    // otherwise if found
    //do {
    //    QuadlistNode<Entry<K, V>* >* lower = p->below;
    //    qlist->data->remove(p);
    //    p = lower;
    //    qlist = qlist->succ;
    //} while (qlist->succ);
    do {
        QuadlistNode<Entry<K, V>* >* lower = p->below;
        qlist->data->remove(p);
        p = lower;
    } while (qlist = qlist->succ);
    while (!empty() && list_->first()->data->empty())
        list_->remove(list_->first());
    return true;
}

#endif

