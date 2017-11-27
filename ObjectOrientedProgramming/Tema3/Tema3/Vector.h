//
// Created by Lucian on 21/05/2017.
//

#ifndef TEMA3_VECTOR_H
#define TEMA3_VECTOR_H

#include "cstring"
#include <iostream>

using namespace std;

template <typename Element, int scaleRate>
class Vector {
private:

    int capacity = scaleRate;

    int size;

    Element* myArray;

    void reallocate() {
        Element* oldArray = myArray;

        myArray = new Element[capacity + scaleRate];

        capacity += scaleRate;

        std::memcpy(myArray, oldArray, size * sizeof(Element));

        delete [] oldArray;
    }

public:
    Vector() : myArray(new Element[scaleRate]), size(0) {}

    void pushBack(Element el) {
        if(size == capacity) {
            reallocate();
        }
        myArray[size++] = el;
    }

    void remove(Element el) {
        for(int i = 0; i < size; i++) {
            if(myArray[i] == el) {
                memcpy(myArray + i, myArray + i + 1, size - i - 1);
                size--;
                break;
            }
        }
    }

    void print() {
        cout<<size<<" "<<capacity<<endl;
        for(int i = 0; i < size; i++) {
            cout<<myArray[i]<<" ";
        }
        cout<<endl;
    }

    ~Vector() {
        delete [] myArray;
        myArray = nullptr;
    }
};


#endif //TEMA3_VECTOR_H
