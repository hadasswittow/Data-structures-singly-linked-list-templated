//
// Created by hadasswittow on 12/16/19.
//

#ifndef LINKEDLISTIMP_LINKEDLIST_H
#define LINKEDLISTIMP_LINKEDLIST_H

#include <stdlib.h>
#include <iostream>

template <typename T>
class LinkedList {
private:
    class Node {
    public:
        friend class LinkedList;
        Node(T val,Node * next):m_val(val),m_next(next){};
        Node(T val):m_next(NULL),m_val(val){};
    private:

        Node *m_next;
        T m_val;
    };
    Node *m_head;
public:
    class Iterator;
    LinkedList():m_head(NULL){};
    ~LinkedList();
    friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list){
        for ( LinkedList<int>::Iterator iterator = list.begin();
              iterator != list.end(); iterator++)
        {
            os << *iterator << " ";
        }
        return os;
    }

    void insert(T value);
    void popFront();
    Iterator begin() const{ return Iterator(m_head); }
    Iterator end() const { return Iterator(NULL); }
    class Iterator
    {
    public:

        Iterator(const Node* pNode):
                m_pCurrentNode (pNode) { }

        Iterator& operator=(Node* pNode)
        {
            this->m_pCurrentNode = pNode;
            return *this;
        }

        // Prefix ++ overload
        Iterator& operator++()
        {
            if (m_pCurrentNode)
                m_pCurrentNode = m_pCurrentNode->m_next;
            return *this;
        }

        // Postfix ++ overload
        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }

        bool operator!=(const Iterator& iterator)
        {
            return m_pCurrentNode != iterator.m_pCurrentNode;
        }

        int operator*()
        {
            return m_pCurrentNode->m_val;
        }

    private:
        const Node* m_pCurrentNode;
    };


};
template <typename T>
inline LinkedList<T>::~LinkedList(){
    Node *temp = m_head;
    Node *temp_next;
    while(temp){
        temp_next = temp->m_next;
        delete(temp);
        temp = temp_next;
    }
}
template <typename T>
inline void LinkedList<T>::insert(T value){

    Node* temp = m_head;
    m_head = new Node(value, temp);
}
template <typename T>
inline void LinkedList<T>::popFront(){
    Node* temp = m_head;
    if(m_head){
        m_head =m_head->m_next;
        delete(temp);
    }
}
#endif //LINKEDLISTIMP_LINKEDLIST_H
