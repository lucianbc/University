#include <iostream>

#include "LifecycleManager.h"

#include "Heap.h"

using namespace std;

LifecycleManager manager;

long int counter = 0;

void drop(LifecycleManager& manager, long int time) {
    cout<<"drop\n";
    manager.register_function(drop, time + 5);
}

void move(LifecycleManager& manager, long int time) {
    cout<<"move\n";
    manager.register_function(move, time + 7);
}

void show(LifecycleManager& mgr, long int time) {
    cout<<"show\n";
    manager.register_function(show, time + 10);
}

void test_manager() {
    manager.register_function(move, counter + 2);
    manager.register_function(drop, counter + 5);
    manager.register_function(show, counter + 13);

    while (true) {
        counter++;
        manager.execute(counter);
    }

}

void test_heap() {
    Heap<int, 10> heap([](key_type n1, key_type n2) -> bool { return n1 < n2; });

    for (int i = 1; i <= 3; i++) {
        heap.insert(i, i);
    }

    for (int i = 0; i < heap.get_size(); i++) {
        cout<<heap.get_array()[i]->key<<" ";
    }
    cout<<endl;

    heap.remove_first();

    for (int i = 0; i < heap.get_size(); i++) {
        cout<<heap.get_array()[i]->key<<" ";
    }
    cout<<endl;

    int fp;

    while (heap.remove_first(fp)) {
        cout<<fp<<endl;
    }
}

int main() {

//    test_heap();

    test_manager();
    return 0;
}