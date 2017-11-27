//
// Created by lucian on 18-Mar-17.
//

#include "LinkedListTester.h"
#include "LinkedList.h"

void LinkedListTester::test() {
    LinkedList<std::string> l1;

//    cout<<*l1.begin()<<" "<<*l1.end()<<" "<<l1.getLength()<<endl;

    l1.pushBack("one");
    l1.pushFront("two");

    for(string s : l1) {
        cout<<s<<" ";
    }
    cout<<endl;

    LinkedList<string> l2(l1);

    l1.pushBack("step");

    for(string s : l2) {
        cout<<s<<" ";
    }
    cout<<endl;

    LinkedList<string> l3;

    l3.pushBack("twice");

    l1.append(l3);

    cout<<"aici ajunge\n";

    for(string s : l1) {
        cout<<s<<" ";
    }
    cout<<endl;

    l1.removeFront();

    for(string s : l1) {
        cout<<s<<" ";
    }
    cout<<endl;

//    LinkedList<std::string> l2 = l1;
//    l2.pushBack("two");
//    for(auto it = l2.begin(); it != l2.end(); ++it) cout<<*it<<" ";
//    cout<<endl;
//    for(auto it = l1.begin(); it != l1.end(); ++it) cout<<*it<<" ";
//    cout<<endl;
}
