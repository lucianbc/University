//
// Created by lucian on 02.12.2017.
//

#include "LifecycleManager.h"


LifecycleManager::LifecycleManager() : queue([](key_type n1, key_type n2) -> bool { return n1 < n2; }) {}

void LifecycleManager::register_function(action func, key_type exec_time) {
    queue.insert(func, exec_time);
}

void LifecycleManager::execute(key_type up_to) {
    key_type top_priority;

    while (queue.get_first_priority(top_priority) && top_priority <= up_to) {
        action a;
        if (queue.remove_first(a)) {
            a(*this, top_priority);
        }
    }
}
