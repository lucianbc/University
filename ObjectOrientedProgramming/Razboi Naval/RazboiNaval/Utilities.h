//
// Created by Lucian on 23/04/2017.
//

#ifndef RAZBOINAVAL_UTILITIES_H
#define RAZBOINAVAL_UTILITIES_H

#include <vector>
#include <string>
#include <sstream>

#include "ShipWar.h"

using namespace std;

class Utilities {
public:
    static vector<string> split(string input, char token) {
        string tmp;
        stringstream inputStream;
        inputStream<<input;
        vector<string> rez;
        while(getline(inputStream, tmp, token)) {
            if(tmp.length() > 0)
                rez.push_back(tmp);
        }
        return rez;
    }

    static int strToInt(string s) {
        istringstream stream(s);
        int val;
        stream>>val;
        return val;
    }

    static string shapeToString(Shape shape) {
        if(shape == Shape::CRUCISATOR || shape == Shape::CRUCISATOR_SCUT) {
            return "Crucisator";
        } else if (shape == Shape::DISTRUGATOR) {
            return "Distrugator";
        } else if(shape == Shape::SUBMARIN) {
            return "Submarin";
        } else {
            return "Salupa";
        }
    }

    static string actionToStrint(Actions action) {
        if(action == Actions::Nothing) {
            return "Nothing";
        } else if(action == Actions::Regenerate) {
            return "Regenerate";
        } else if(action == Actions::Attack) {
            return "Attack";
        } else if(action == Actions::Self_destroy) {
            return "Self Destroy";
        }
        return "";
    }
};


#endif //RAZBOINAVAL_UTILITIES_H
