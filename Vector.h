#ifndef _VECTOR_H
#define _VECTOR_H
#include <cassert>
#include <cstdlib>

template <typename T> static bool lt(T *a, T *b)
{
    return lt(*a, *b);
}

template <typename T> static bool lt(T& a, T& b)
{
    return a < b;
}

template <typename T> static bool eq(T* a, T* b)
{
    return eq(*a, *b);
}

template <typename T> static bool eq(T& a, T& b)
{
    return a == b;
}

template<typename T>
void permute(Vector<T>& v)
{
    for (int i = v.size(); i > 0; i--)
        swap(v[i-1], v[rand() % i]);
}

#define DEFAULTcapacity_ 8

template <typename T> 
class Vector 
{
    private:
        int size_;
        int capacity_;
        T* elem_;
        void copyFrom(T* const from, int lo, int hi);
        void expand();
        void shrink();
        bool bubble(int lo, int hi);
        void bubbleSort(int lo, int hi);
        void exchange(int i, int j);
        int selectMax(int lo, int hi);
        void selectionSort(int lo, int hi);
        void merge(int lo, int hi);
        void mergeSort(int lo, int hi);
        int partition(int lo, int hi);
        void quickSort(int lo, int hi);
        void heapSort(int lo, int hi);
    public:
        Vector(int c = DEFAULTcapacity_) { elem_ = new T[capacity_ = c]; size_ = 0; }
        Vector(T* from, int lo, int hi) { copyFrom(from, lo, hi); }
        Vector(T* from, int n) { copyFrom(from, 0, n); }
        Vector(Vector<T> const& V, int lo, int hi) { copyFrom(V.data(), lo, hi); }
        Vector(Vector<T> const& V) { copyFrom(V.data(), 0, V.size()); }
        ~Vector() { delete [] elem_; }
        int size() const { return size_; }
        T* data() const { return elem_; }
        bool empty() const { return size_ <= 0; }
        bool isSorted() const;
        int find(T const& elem) const { return find(elem, 0, (int)size_); }
        int find(T const& elem, int lo, int hi) const;
        int search(T const& elem) const
        {
            return (0 >= size_) ? -1 : search(elem, (int)0, (int)size_);
        }
        int search(T const& elem, int lo, int hi) const;
        T& operator[](int r) const;
        Vector<T>& operator=(Vector<T> const&);
        T remove(int r);
        int remove(int lo, int hi);
        int insert(int r, T const& elem);
        int insert(T const& elem) { insert(size_, elem); }
        void sort(int lo, int hi);
        void sort() { sort(0, size_); }
        void unsort(int lo, int hi);
        void unsort() { unsort(0, size_); }
        int deduplicate();
        int uniquify();
        void traverse(void (*)(T&));
        template <typename VST> void traverse(VST&);
};

template<typename T>
void Vector<T>::copyFrom(T* const from, int lo, int hi)
{
    elem_ = new T[capacity_ = 2*(hi-lo)];
    size_ = 0;
    while (lo < hi) {
        elem_[size_] = from[lo];
        size_++;
        lo++;
    }
}

template<typename T>
void Vector<T>::expand() 
{
    if (size_ < capacity_)
        return;
    if (capacity_ < DEFAULTcapacity_)
        capacity_ = DEFAULTcapacity_;
    T* oldElem = elem_;
    elem_ = new T[capacity_ <<= 1];
    for(int i = 0; i < size_; i++)
        elem_[i] = oldElem[i];
    delete [] oldElem;
}

template<typename T>
void Vector<T>::shrink()
{
    if (capacity_ < (DEFAULTcapacity_ << 1))
        return;
    if ((size_ << 2) > capacity_)
        return;
    T* oldElem = elem_;
    elem_ = new T[capacity_ >>= 1];
    for(int i = 0; i < size_; i++)
        elem_[i] = oldElem[i];
    delete [] oldElem;
}

template<typename T>
bool Vector<T>::isSorted() const
{
    int n = 0;
    for (int i = 1; i < size_; i++)
        if (elem_[i - 1] > elem_[i])
            n++;
    return n == (size_ - 1);
}

template<typename T>
int Vector<T>::find(T const& elem, int lo, int hi) const
{
    //assert(lo >= 0 && lo <= hi && hi < size_);
    while (hi > lo) {
        if (elem_[hi] == elem)
            break;
        hi--;
    }
    return hi;
}

template<typename T>
int Vector<T>::search(T const& elem, int lo, int hi) const
{
    return (rand() % 2) ? binSearch(elem_, elem, lo, hi) : fibSearch(elem_, elem, lo, hi);
}

template<typename T>
int Vector<T>::insert(int r, T const& elem)
{
    assert(r >= 0 && r <= size_);
    expand();
    for (int i = size_; i > r; i--)
        elem_[i] = elem_[i - 1];
    elem_[r] = elem;
    size_++;
    return r;
}

template<typename T>
T& Vector<T>::operator[](int r) const
{
    assert(r >= 0 && r < size_);
    return elem_[r];
}

template<typename T>
void Vector<T>::unsort(int lo, int hi)
{
    T* V = elem_ + lo;
    for (int i = hi - lo; i > 0; i--)
        swap(V[i - 1], V[rand() % i]);
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V)
{
   if (elem_)
       delete [] elem_;
   copyFrom(V.data(), 0, V.size());
   return *this;
}

template<typename T>
int Vector<T>::remove(int lo, int hi)
{
    if (lo == hi)
        return 0;
    while (hi < size_) {
        elem_[lo] = elem_[hi];
        lo++;
        hi++;
    }
    size_ = lo;
    shrink();
    return hi - lo;
}

template<typename T>
T Vector<T>::remove(int r)
{
    T elem = elem_[r];
    remove(r, r + 1);
    return elem;
}

template<typename T>
int Vector<T>::deduplicate()
{
    int oldSize = size_;
    int i = 1;
    while (i < size_)
        (find(elem_[i], 0, i) < 0) ? i++ : remove(i);
    return oldSize - size_;
}

template<typename T>
int Vector<T>::uniquify()
{
    int i = 0, j = 1;
    while (j < size_) {
        if (elem_[i] != elem_[j]) {
            elem_[i] = elem_[j];
            i++;
        }
        j++;
    }
    size_ = ++i;
    shrink();
    return j - i;
}

template<typename T>
void Vector<T>::traverse(void (*visit)(T&))
{
    for (int i = 0; i < size_; i++)
        visit(elem_[i]);
}

template<typename T> template<typename VST>
void Vector<T>::traverse(VST& visit)
{
    for (int i = 0; i < size_; i++)
        visit(elem_[i]);
}

template<typename T>
void Vector<T>::quickSort(int lo, int hi)
{
    if (hi - lo < 2) return; // hi - lo == 1
    int mi = partition(lo, hi - 1);
    quickSort(lo, mi);
    quickSort(mi + 1, hi);
}

template<typename T>
int Vector<T>::partition(int lo, int hi)
{
    swap(elem_[lo], elem_[lo + rank() % (hi - lo + 1)]);
    T pivot = elem_[lo];
    while (lo < hi) {
        while ((lo < hi) && (pivot <= elem_[hi]))
            hi--;
        elem_[lo] = elem_[hi];
        while ((lo < hi) && (pivot >= elem_[lo]))
            lo++;
        elem_[hi] = elem_[lo];
    } //assert: lo == hi
    elem_[lo] = pivot;
    return lo;
}

template<typename T>
void Vector<T>::traverse(void (*visit)(T&))
{
    for (int i = 0; i < size_; ++i)
        visit(elem_[i]);
}

template<typename T> template<typename VST>
void Vector<T>::traverse(VST& visit)
{
    for (int i = 0; i < size_; ++i)
        visit(elem_[i]);
}

template<typename T>
void Vector<T>::sort(int lo, int hi)
{
    switch(rand() % 5) {
        case 1: bubbleSort(lo, hi); break;
        case 2: selectionSort(lo, hi); break;
        case 3: mergeSort(lo, hi); break;
        case 4: heapSort(lo, hi); break;
        defautl: quickSort(lo, hi); break;
    }
}


template<typename T>
T majEleCandidate(Vector<T> A)
{
    T maj;
    
    for (int c = 0, i = 0; i < A.size(); i++) {
        if (c == 0) {
            maj = A[i];
            c = 1;
        } else
            (maj == A[i]) ? c++ : c--;
    }
    return maj;
}

template<typename T>
bool majEleCheck(Vector<T> A, T maj)
{
    int occurrence = 0;
    for (int i = 0; i < A.size(); i++) {
        if (A[i] == maj)
            occurrence++;
    }
    return 2 * occurrence > A.size();
}

template<typename T>
bool majority(Vector<T> A, int& maj)
{
    maj = majEleCandidate(A);
    return majEleCheck(A, maj);
}
#endif
