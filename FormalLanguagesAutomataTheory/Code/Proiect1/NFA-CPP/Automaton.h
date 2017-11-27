//
// Created by lucian on 02-Mar-17.
//

#ifndef P1_AUTOMATON_H
#define P1_AUTOMATON_H


#include <string>
#include <list>
#include <iostream>
#include <map>

class Automaton {

    struct Transition {

        struct State {
            std::string tag;
            bool isFinal;
            std::list<Transition> transitions;
        };

        State* next;
        char command;
    };

    Transition::State* initialState, *currentState;
    std::map<std::string, Transition::State> states;

public:
    Automaton();
    void citeste(std::istream &fin);
    void afisare(std::ostream &out);
    bool evaluate(std::string word);

private:
    virtual void evaluate(std::string word, int i, bool &rez);
    void reset();
};


#endif //P1_AUTOMATON_H
