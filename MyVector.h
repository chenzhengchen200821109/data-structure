#if !defined MiniVector_h
#define MiniVector_h

#include <cassert>
typedef int Rank;
#define DEFAULT_CAPACITY 3

template<typename T> 
class Vector
{
    private:
        Rank _size;
        int _capacity;
        T* _elem;
        void copyFrom(T* const A, Rank lo, Rank hi);
        void expand();
        void shrink();
    public:
        // constructors and destructor
        Vector(int c = DEFAULT_CAPACITY) { _elem = new T[_capacity = c]; _size = 0; }
        Vector(T* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }
        Vector(T* A, Rank n) { copyFrom(A, 0, n); }
        Vector(const Vector<T>& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); }
        Vector(const Vector<T>& V) { copyFrom(V._elem, 0, V._size); }
        ~Vector() { delete [] _elem; }
        // readable interface
        Rank size() const { return _size; }
        bool empty() const { return _size <= 0; }
        Rank find(const T& e) const { return find(e, 0, (Rank)_size); }
        Rank find(const T& e, Rank lo, Rank hi) const;
        // writable interface
        T& operator[](Rank r) const;
        Vector<T>& operator=(const Vector<T>&); // assignment constructor
        T remove(Rank r);
        int remove(Rank lo, Rank hi);
        Rank insert(Rank r, const T& e);
        Rank insert(const T& e) { return insert(_size, e); }
};

template<typename T>
void Vector<T>::copyFrom(T* const A, Rank lo, Rank hi)
{
    _elem = new T[_capacity = 2*(hi - lo)];
    _size = 0;
    while (lo < hi)
        _elem[_size++] = A[lo++];
}

template<typename T>
void Vector<T>::expand()
{
    if (_size < _capacity) return;
    if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    T* oldElem = _elem;
    _elem = new T[_capacity << 1];
    for (int i = 0; i < _size; i++)
        _elem[i] = oldElem[i];
    delete [] oldElem;
}

template<typename T>
Rank Vector<T>::find(const T& e, Rank lo, Rank hi) const
{
    assert(0 <= lo);
    assert(lo < hi);
    assert(hi < _size);
    while ((lo < hi--) && (_elem[hi] != e))
        ;
    return hi;
}

template<typename T>
void Vector<T>::shrink()
{
    if (_capacity < (DEFAULT_CAPACITY << 1)) return;
    if ((_size << 2) > _capacity) return;
    T* oldElem = _elem; _elem = new T[_capacity >> 1];
    for (int i = 0; i < _size; i++)
        _elem[i] = oldElem[i];
    delete [] oldElem;
}

template<typename T>
T& Vector<T>::operator[](Rank r) const
{
    assert(r >= 0);
    assert(r < _size);
    return _elem[r];
}

// assignment constructor
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& V)
{
    if (_elem) 
        delete [] _elem;
    copyFrom(V._elem, 0, V.size());

    return *this;
}

template<typename T>
T Vector<T>::remove(Rank r)
{
    assert(r >= 0);
    assert(r < _size);
    T e = _elem[r];
    remove(r, r+1);
    return e;
}

template<typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
    assert(lo >= 0);
    assert(hi >= lo);
    //assert(hi < _size);
    if (lo == hi) return 0;
    while (hi < _size)
        _elem[lo++] = _elem[hi++];
    _size = lo;
    shrink();
    return hi - lo;
}

template<typename T>
Rank Vector<T>::insert(Rank r, const T& e)
{
    assert(r >= 0);
    assert(r <= _size);
    expand();
    for (int i = _size; i > r; i--)
        _elem[i] = _elem[i - 1];
    _elem[r] = e;
    _size++;
    
    return r;
}

#endif
