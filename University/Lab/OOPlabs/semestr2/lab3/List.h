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
    typedef _iterator<node_type> iterator;
    
    List();
    ~List();

    iterator    begin();
    iterator    end();
    void        clear();
    bool        empty();
    iterator    find(const node_type& val);
    void        pop_front();
    void        push_front();
    void        remove(const node_type val);
    int         size();
    void        splice();

private:
    node_type*  head;
    iterator*   first;
    iterator*   last;
};