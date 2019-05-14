#include "Iterator.h"


template <typename T>
T& _iterator<T>::operator* () {
    return *ptr;
}


template <typename T>
void _iterator<T>::operator++ () {
    ptr = ptr->next;
}


template <typename T>
void _iterator<T>::operator++ (int) {
    ptr = ptr->next;
}


template <typename T>
bool _iterator<T>::operator== (const it_type &_iter) const {
    return (ptr == _iter.ptr);
}


template <typename T>
bool _iterator<T>::operator!= (const it_type &_iter) const {
    return !(*this == _iter);
}