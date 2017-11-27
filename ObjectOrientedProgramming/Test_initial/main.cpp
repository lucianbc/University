#include <iostream>
#include <sstream>
#include "Prajitura.h"

using namespace std;

//vector<string> parse(string input, char delim) {
//    vector<string> words;
//    int i = input.find(delim, 0);
//    int last = 0;
//    while (i < input.size()) {
//        if(i - last > 0){
//            words.push_back(input.substr((unsigned int) last, (unsigned int) (i - last)));
//        }
//        last = i + 1;
//        i = input.find(delim, (unsigned int) (i + 1));
//    }
//
//    if(input.length() - last > 0){
//        words.push_back(input.substr((unsigned int) last, input.length() - last));
//    }
//
//    return words;
//}

int main() {

    Prajitura prajitura;

    prajitura.run(cin, cout);


//    istringstream parser("as");
//
//    int a;
//
//    parser>>a;
//    if(!parser.fail())
//        cout<<a<<endl;
//    else
//        cout<<"failed\n";

//    int a;
//    istringstream("123") >> a;

//    string s;
//    getline(cin, s);
//
//    cout<<s.find(" ")<<endl;

    return 0;
}
