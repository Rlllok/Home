/************************************************************************       
 * file: List.h                                                         
 * List class declaration                                                
 * author: Novikov Alexander KV-72                                              
 * written: 02/05/2019                                                          
 * last modified: 1/06/2019                                                    
 ************************************************************************/
#pragma once
#include "stdlib.h"
#include <iostream>


template <class T>
class List {
    struct ListNode
    {
        T data;
        ListNode* next;
        ListNode() {
            next = NULL;
        }
        ListNode(T dat){
            data = dat;
        }
        void Print() {
            std::cout << data;
        }
    };

public:
    typedef ListNode node_type;
    typedef Iterator<node_type> iterator;
    
    List();
    ~List();

    iterator begin();
    iterator end();
    void clear();
    bool empty();
    iterator find(const node_type& val);
    void pop_front();
    void push_front(const node_type val);
    void remove(node_type val);
    int size();
    void splice(iterator where, List<T>& right);
    void print();
    T getData();

private:
    node_type*  head;
    iterator*   first;
    iterator*   last;
};


template <typename T>
List<T>::List() : head(new ListNode), first(new iterator(head)), last(new iterator(head)) {}


template <typename T>
List<T>::~List() {
    ListNode* buff = head;

    while (head->next != NULL) {
        buff = head;
        head = head->next;
        delete buff;
    }

    delete first;
    delete last;
}


template <typename T>
typename List<T>::iterator List<T>::begin() {
    return *first;
}


template <typename T>
typename List<T>::iterator List<T>::end() {
    return *last;
}


template <typename T>
void List<T>::clear() {
    ListNode* buff = head;

    while (head->next != NULL) {
        buff = head;
        head = head->next;
        delete buff;
    }

    first = NULL;
    last = NULL;
}


template <typename T>
bool List<T>::empty() {
    if (head->next == NULL) return true;


    return false;
}


template <typename T>
void List<T>::push_front(const node_type val) {
    delete first;
    node_type* tmp = new node_type(val);
    tmp->next = head;
    head = tmp;
    first = new iterator(tmp);
}


template<typename T>
void List<T>::pop_front() {
    head = head->next;
    delete first;
    first = new iterator(head);
}


template<typename T>
int List<T>::size() {
    int elements_count = 0;
    node_type* iter = head;

    while (iter->next) {
        elements_count++;
        iter = iter->next;
    }

    return elements_count;
}


template<typename T>
typename List<T>::iterator List<T>::find(const node_type& val) {
    node_type* iter = head;
    bool finded = false;

    while (iter->next) {
        if (iter->data == val.data) {
            finded = true;
            break;
        }
        iter = iter->next;
    }
    
    iterator* tmp = new iterator(iter);
    if (finded) return *tmp;
    else return NULL;
}


template<typename T>
void List<T>::remove(node_type val) {
    node_type* iter = head;
    bool finded = false;

    if (head->data == val.data) {
        head = head->next;
        delete iter;
        delete first;
        first = new iterator(head);
        return;
    }

    while (iter->next) {
        if (iter->next->data == val.data) {
            node_type* tmp = iter->next;
            iter->next = iter->next->next;
            delete tmp;
            break;
        }
        iter = iter->next;
    }
}


template<typename T>
void List<T>::splice(iterator where, List<T>& right) {
    node_type tmp = (*where);
    this->remove(tmp.data);
    right.push_front(tmp);
}


template <typename T>
void List<T>::print() {
    if (empty()) {
        std::cout << "List is empty" << std::endl;
    }
    else {
        node_type* iter = head;

        while(iter->next) {
            iter->Print();
            std::cout << std::endl << std::endl;
            iter = iter->next;
        }
    }
}
