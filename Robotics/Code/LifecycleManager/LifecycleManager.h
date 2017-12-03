//
// Created by lucian on 02.12.2017.
//

#ifndef LIFECYCLEMANAGER_LIFECYCLEMANAGER_H
#define LIFECYCLEMANAGER_LIFECYCLEMANAGER_H

#include "Heap.h"

class LifecycleManager;

typedef void (*action)(LifecycleManager&, key_type);

class LifecycleManager {
    Heap<action, 20> queue;

public:
    LifecycleManager();

    void register_function(action func, key_type exec_time);

    void execute(key_type up_to);

    int size() {
        return queue.get_size();
    }
};


#endif //LIFECYCLEMANAGER_LIFECYCLEMANAGER_H
