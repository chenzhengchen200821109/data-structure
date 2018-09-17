#ifndef _BITMAP_H
#define _BITMAP_H

#include <bitset>

// The class template bitset represents a fixed-size sequence of N bits.
// Bitsets can be manipulated by standard logic operators and converted 
// to and from strings and integers.
template<size_t N>
class Bitmap
{
    public:
        void set(int i);
        void clear(int i);
        bool test(int i) const;
    private:
        std::bitset<N> set_;
};

template<size_t N>
void Bitmap<N>::set(int i)
{
    size_t pos = set_.size() - i - 1;
    set_.set(pos, true);
}

template<size_t N>
void Bitmap<N>::clear(int i)
{
    size_t pos = set_.size() - i - 1;
    set_.set(pos, false);
}

template<size_t N>
bool Bitmap<N>::test(int i) const
{
    size_t pos = set_.size() - i - 1;
    return set_.test(pos);
}

#endif
