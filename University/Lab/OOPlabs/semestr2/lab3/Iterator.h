#pragma once
#include "stdlib.h"


template<typename T>
class Iterator {
private:
    T* ptr;
public:
    typedef T value_type;
    typedef Iterator<T> it_type;
    Iterator() { ptr = 0; }
    Iterator(T* _ptr) { ptr = _ptr; }

    T& operator* ();
    void operator++ ();
    void operator++ (int);
    void operator= (const it_type& _iter);

    bool operator== (const it_type& _iter) const;
    bool operator!= (const it_type& _iter) const;
    bool empty() { return ptr == NULL;}
};


#include "Iterator.h"


template <typename T>
T& Iterator<T>::operator* () {
    return *ptr;
}


template <typename T>
void Iterator<T>::operator++ () {
    ptr = ptr->next;
}


template <typename T>
void Iterator<T>::operator= (const it_type& _iter) {
    ptr = _iter.ptr;
}


template <typename T>
void Iterator<T>::operator++ (int) {
    ptr = ptr->next;
}


template <typename T>
bool Iterator<T>::operator== (const it_type &_iter) const {
    return (ptr == _iter.ptr);
}


template <typename T>
bool Iterator<T>::operator!= (const it_type &_iter) const {
    return !(*this == _iter);
}