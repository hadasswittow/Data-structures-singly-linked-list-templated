//
// Created by hadasswittow on 12/16/19.
//

#ifndef LINKEDLISTIMP_LINKEDLIST_H
#define LINKEDLISTIMP_LINKEDLIST_H

#include <stdlib.h>
#include <iostream>

template<typename T>
class LinkedList {
private:
    struct Node {
        friend class LinkedList;

        Node(T val, Node *next = NULL) : m_val(val), m_next(next) {};
        Node *m_next;
        T m_val;
    };

    Node *m_tail;
    Node *m_head;
public:
    class Iterator;

    LinkedList() : m_tail(NULL), m_head(m_tail) {};

    ~LinkedList();

    void pushFront(T value);

    void pushBack(T value);

    void popFront();

    void popBack();

    void remove(T val);

    T front();

    void clear();

    LinkedList& operator=(const LinkedList& other );
    friend std::ostream &operator<<(std::ostream &os, const LinkedList<T> &list) {
        for (LinkedList<T>::Iterator iterator = list.begin();
             iterator != list.end(); ++iterator) {
            if (iterator->m_next == list.m_tail)
                os << *iterator << std::endl;
            else
                os << *iterator << " -> ";
        }
        return os;
    }

    Iterator begin() const { return Iterator(m_head); }

    Iterator end() const { return Iterator(m_tail); }

    class Iterator {
    public:

        Iterator(const Node *const pNode) : m_node(pNode) {}

        // Prefix ++ overload
        Iterator &operator++() {
            if (m_node)
                m_node = m_node->m_next;
            return *this;
        }

        // Postfix ++ overload
        Iterator operator++(int) {
            Iterator iterator(*this);
            ++(*this);
            return iterator;
        }

        bool operator!=(const Node &node) {
            return (m_node != node);
        }

        bool operator!=(const Iterator &iterator) {
            return (m_node != iterator.m_node);
        }

        bool operator==(const Iterator &iterator) {
            return (m_node == iterator.m_node);
        }

        const Node *operator->() const {
            return m_node;
        }

        T operator*() {
            return m_node->m_val;
        }

    private:
        const Node *m_node;
    };


};

template<typename T>
inline LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other ){
    this->clear();
    for (LinkedList<T>::Iterator iterator = other.begin();
         iterator != other.end(); ++iterator) {
        pushFront(*iterator);
    }
    return *this;
}
template<typename T>
inline void LinkedList<T>::clear() {
    Node *temp = m_head;
    Node *temp_next;
    while (temp != m_tail) {
        temp_next = temp->m_next;
        delete (temp);
        temp = temp_next;
    }
    m_head = m_tail;
}

template<typename T>
inline void LinkedList<T>::pushFront(T value) {
    m_head = new Node(value, m_head);
}

template<typename T>
inline void LinkedList<T>::popFront() {
    if (m_head == m_tail) {
        throw std::underflow_error("Underflow! There are no elements in list to pop!\n");
    }
    Node *temp = m_head;
    m_head = m_head->m_next;
    delete (temp);
}

template<typename T>
inline void LinkedList<T>::pushBack(T value) {
    if (m_head == m_tail)
        m_head = new Node(value, m_tail);
    else {
        Node *node = new Node(value, m_tail);
        Node *temp = m_head;
        while (temp->m_next != m_tail) {
            temp = temp->m_next;
        }
        temp->m_next = node;
    }

}

template<typename T>
inline T LinkedList<T>::front() {
    return m_head->m_val;
}

template<typename T>
inline void LinkedList<T>::popBack() {
    if (m_head == m_tail) {
        throw std::underflow_error("There are no elements in list to pop!\n");
    }
    if (m_head->m_next == m_tail) {
        delete (m_head);
        m_head = m_tail;
    } else {
        Node *temp = m_head;
        while (temp->m_next->m_next != m_tail) {
            temp = temp->m_next;
        }
        delete (temp->m_next);
        temp->m_next = m_tail;
    }

}

template<typename T>
inline void LinkedList<T>::remove(T val) {
    Node *temp = m_head->m_next;
    if(m_head->m_val == val){
        delete(m_head);
        m_head = temp;
    }
    else {
        temp = m_head;
        Node *temp1;
        while (temp != m_tail ) {
            temp = temp->m_next;
            if(temp->m_next->m_val == val){
                temp1 = temp->m_next->m_next;
                delete (temp->m_next);
                temp->m_next = temp1;
                return;
            }
        }

    }
}

#endif //LINKEDLISTIMP_LINKEDLIST_H
