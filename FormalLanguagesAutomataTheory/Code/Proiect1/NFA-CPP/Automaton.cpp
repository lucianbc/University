//
// Created by lucian on 02-Mar-17.
//

#include "Automaton.h"

using namespace std;

Automaton::Automaton() {
    this->currentState = nullptr;
    this->initialState = nullptr;
}

void Automaton::citeste(istream &fin) {
    int s, t;
    fin>>s>>t;

    for(int i = 0; i < s; i++) {
        Transition::State thisState;
        fin>>thisState.tag>>thisState.isFinal;
        this->states[thisState.tag] = thisState;
        if(i == 0) {
            this->currentState = &this->states[thisState.tag];
            this->initialState = &this->states[thisState.tag];
        }
    }

    for(int i = 0; i < t; i++) {
        string o, d;
        char c;
        fin>>o>>d>>c;
        Transition tr;
        tr.command = c;
        tr.next = &(this->states[d]);
        this->states[o].transitions.push_back(tr);
    }
}

void Automaton::afisare(ostream &out) {
    for(map<string, Transition::State>::iterator it = states.begin(); it != states.end(); ++it ) {
        out<<it->second.tag<<" "<<it->second.isFinal<<endl;

        for(list<Transition>::iterator lit = it->second.transitions.begin(); lit != it->second.transitions.end(); ++lit) {
            out<<"("<<lit->command<<" "<<lit->next->tag<<"), ";
        }
        out<<endl;
    }
}

bool Automaton::evaluate(string word) {
    bool rez = false;
    int i = 0;
    evaluate(word, i, rez);
    reset();
    return rez;
}

void Automaton::evaluate(string word, int i, bool &rez) {
    if(i == word.length())
        rez = rez || currentState->isFinal;
    Transition::State *cacheState = this->currentState;
    for(list<Transition>::iterator lit = currentState->transitions.begin(); lit != currentState->transitions.end(); ++lit) {
        if(lit->command == word[i]) {
            currentState = lit->next;
            evaluate(word, i + 1, rez);
            currentState = cacheState;
        }
    }
}

void Automaton::reset() {
    this->currentState = this->initialState;
}

