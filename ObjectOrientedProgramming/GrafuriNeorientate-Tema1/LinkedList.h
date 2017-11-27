//
// Created by lucian on 18-Mar-17.
//

#ifndef GRAFURINEORIENTATE_TEMA1_CUSTOM_LIST_H
#define GRAFURINEORIENTATE_TEMA1_CUSTOM_LIST_H

#include <cstddef>
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T> class LinkedListIterator;
template <typename T> class LinkedListConstIterator;

template <typename T> struct ListNode;

template <typename T> class LinkedList {

public:
    typedef LinkedListIterator<T> iterator;
    typedef LinkedListConstIterator<T> const_iterator;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef T value_type;
    typedef ListNode<T> node;
    typedef ListNode<T>* pointer;
    typedef ListNode<T>& reference;

private:

    friend class LinkedListIterator<value_type>;
    friend struct ListNode<value_type>;

    int length;

    const pointer null_node;
    pointer first, last;

public:

    /** Default constructor */
    LinkedList() : length(-1), null_node(new node(*this)), first(null_node), last(null_node) {}

    /** Copy constructor */
    LinkedList(const LinkedList<value_type>& other) : length(-1), null_node(new node(*this)), first(null_node), last(null_node) {
        for(const_iterator it = other.cbegin(); it != other.cend(); ++it) {
            pushBack(*it);
        }
    }
    /** Copy assignment operator */
    LinkedList<value_type>&operator=(LinkedList<value_type>& other) {
        pointer crt = first;
        while (crt != null_node) {
            pointer next = crt->next;
            delete(crt);
            crt = next;
        }
        first = last = null_node;
        for(const_iterator it = other.cbegin(); it != other.cend(); ++it) {
            pushBack(*it);
        }
        return *this;
    }

    void pushBack(value_type data) {
        pointer newNode = new node(*this);
        newNode->data = data;
        if(first == null_node) {
            first = last = newNode;
        } else {
            last->next = newNode;
            last = newNode;
        }
    }

    void pushFront(value_type data) {
        pointer newNode = new node(*this);
        newNode->data = data;

        if(first == null_node) {
            first = last = newNode;
        } else {
            newNode->next = first;
            first = newNode;
        }
    }

    void removeFront() {
        if(first == null_node) return;
        pointer tmp = first;
        if(first == last) {
            first = last = null_node;
        } else {
            first = first->next;
        }
        delete tmp;
    }

    void append(LinkedList<value_type>& other) {
        if(other.first == other.null_node) return;
        if(first != null_node) {
            last->next = other.first;
        } else {
            first = other.first;
        }
        last = other.last;
        last->next = null_node;
        length += other.length;
        other.first = other.last = other.null_node;
        other.length = 0;
    }

    int getLength() const { return length; }

    iterator begin() { return iterator(*this, first); }
    iterator end() { return iterator(*this, null_node); }
    const_iterator cbegin() const { return const_iterator(*this, first); }
    const_iterator cend() const { return const_iterator(*this, null_node); }

    ~LinkedList() {
        pointer crt = first;
        while (crt != null_node) {
            pointer next = crt->next;
            delete(crt);
            crt = next;
        }
        delete null_node;
        first = last = null_node;
    }
};

template <typename T> class LinkedListIterator {
    friend class LinkedList<T>;

    LinkedList<T> &container;
    ListNode<T> *ptr;
public:
    LinkedListIterator(LinkedList<T> &container) : container(container), ptr(nullptr) { }
    LinkedListIterator(LinkedList<T> &container, ListNode<T> *ptr) : container(container), ptr(ptr) { }
    LinkedListIterator(const LinkedListIterator<T> &other) : container(other.container), ptr(other.ptr) { }
    LinkedListIterator&operator=(LinkedListIterator<T> &other) {
        container = other.container;
        ptr = other.ptr;
        return *this; }
    LinkedListIterator&operator++() { if(ptr) ptr = ptr->next; return *this; }
    bool operator==(const LinkedListIterator& other) { return ptr == other.ptr; }
    bool operator!=(const LinkedListIterator& other) { return ptr != other.ptr; }
    T&operator*(){ if(ptr) return ptr->data; else throw std::invalid_argument("null pointer"); }
};

template <typename T> struct ListNode {
    T data;
    LinkedList<T> &container;
    ListNode<T> *next;

    ListNode(LinkedList<T> &container) : next(container.null_node), container(container) { container.length++; }

    ~ListNode() { container.length--; }
};

template <typename T> class LinkedListConstIterator {
    friend class LinkedList<T>;

    LinkedList<T> &container;
    const ListNode<T> *ptr;

public:
    LinkedListConstIterator(LinkedList<T> &container) : container(container), ptr(nullptr) {};
    LinkedListConstIterator(const LinkedList<T> &container, ListNode<T> *ptr) : container((LinkedList<T> &) container), ptr(ptr) {};
    LinkedListConstIterator(const LinkedListConstIterator<T> &other) : container(other.container), ptr(other.ptr) { }
    LinkedListConstIterator&operator=(LinkedListConstIterator<T> &other) {
        container = other.container;
        ptr = other.ptr;
        return *this;
    }
    LinkedListConstIterator&operator++() { if(ptr) ptr = ptr->next; return *this; }
    bool operator==(const LinkedListConstIterator& other) { return ptr == other.ptr; }
    bool operator!=(const LinkedListConstIterator& other) { return ptr != other.ptr; }
    const T&operator*(){ if(ptr) return ptr->data; else throw std::invalid_argument("null pointer"); }
};


#endif //GRAFURINEORIENTATE_TEMA1_CUSTOM_LIST_H
