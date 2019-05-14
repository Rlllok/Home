#pragma once
#include "stdlib.h"

template<typename T>
class _iterator {
private:
    T* ptr;
public:
    typedef T value_type;
    typedef _iterator<T> it_type;
    _iterator() { ptr = 0; }
    _iterator(T* _ptr) { ptr = _ptr; }

    T& operator* ();
    void operator++ ();
    void operator++ (int);

    bool operator== (const it_type& _iter) const;
    bool operator!= (const it_type& _iter) const;
    bool empty() { return ptr == NULL;}
};