//
// Created by lucian on 02.12.2017.
//

#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H

typedef long int key_type;

template <typename T, int CAPACITY>
class Heap {

    struct Node {
        T value;
        key_type key;

        Node(T value, key_type key) : value(value), key(key) {}
    };

    int capacity;
    int size;
    Node* heap[CAPACITY];

    bool (*comp)(key_type n1, key_type n2);

    void swap(Node* &n1, Node* &n2) {
        Node* temp = n1;
        n1 = n2;
        n2 = temp;
    }

    int position_check(int position) {
        if (position < 0) return 0;
        if (position >= capacity) return capacity - 1;
        return position;
    }

    int left(int i) {
        return position_check(2 * i + 1);
    }

    int right(int i) {
        return position_check(2 * i + 2);
    }

    int parent(int i) {
        return position_check((i - 1) / 2);
    }

    void heapify_down(int position) {
        if (position >= size) return;

        int l = left(position);
        int r = right(position);

        int pos = heap[l] != nullptr && comp(heap[l]->key, heap[position]->key) ? l : position;
        pos = heap[r] != nullptr && comp(heap[r]->key, heap[pos]->key) ? r : pos;

        if (pos != position) {
            swap(heap[position], heap[pos]);
            heapify_down(pos);
        }
    }

    void heapify_up(int position) {
        int p = parent(position);

        if (p == position) return;

        if (comp(heap[position]->key, heap[p]->key)) {
            swap(heap[p], heap[position]);
            heapify_up(p);
        }
    }

public:

    explicit Heap(bool (*compFunc)(key_type , key_type)) : size(0), comp(compFunc), capacity(CAPACITY) {
        for (int i = 0; i < capacity; i++) {
            heap[i] = nullptr;
        }
    }

    int get_capacity() const {
        return capacity;
    }

    int get_size() const {
        return size;
    }

    Node** get_array() {
        return heap;
    }

    bool insert(T el, key_type priority) {
        if (size >= capacity) return false;
        heap[size++] = new Node(el, priority);
        heapify_up(size - 1);
        return true;
    }

    bool get_first(T &resp) {
        if (size == 0) return false;
        resp = heap[0]->value;
        return true;
    }

    bool get_first_priority(key_type &priority) {
        if (size == 0) return false;
        priority = heap[0]->key;
        return true;
    }

    bool remove_first(T &resp) {
        if (!get_first(resp)) return false;
        return remove_first();
    }

    bool remove_first() {
        if (size == 0) return false;
        swap(heap[0], heap[size - 1]);
        delete heap[size - 1];
        heap[size - 1] = nullptr;
        size--;
        heapify_down(0);
        return true;
    }

    virtual ~Heap() {
        while (remove_first()) {
            // the remove_first function does all the job, so the loop can remain empty
        }
    }
};


#endif //HEAP_HEAP_H
