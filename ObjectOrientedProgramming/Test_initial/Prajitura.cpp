//
// Created by lucian on 02-Mar-17.
//

#include "Prajitura.h"
#include <sstream>

using namespace std;

void Prajitura::afiseazaTotal(ostream& out) {

    float suprafataTotala = 0, volumTotal = 0;

    for(vector<Forma*>::iterator it = prajituri.begin(); it != prajituri.end(); ++it) {
        suprafataTotala += (*it)->getSuprafata();
        volumTotal += (*it)->getVolum();
    }

    out<<"cantitatea totala de gem necesara: " <<2 * volumTotal<<endl;
    out<<"cantitatea totala de frisca necesara: " << suprafataTotala;
}

void Prajitura::remove(int x) {
    --x;
    delete prajituri[x];
    prajituri.erase(prajituri.begin() + x);
}

void Prajitura::add(string tip, istream& in, ostream& out) {
    Forma* crt;

    if(tip == "cerc") crt = new Cilindru;
    else if (tip == "dreptunghi") crt = new Paralelipiped;
    else if (tip == "patrat") crt = new Patratic;
    else if (tip == "triunghi") crt = new Prisma;
    else { out<<"Operatie nerecunoscuta"; return; }

    crt->citire(in, out);

    out<<"Pentru prajitura introdusa aveti nevoie de "<<crt->getVolum() * 2
       <<" grame de gem si "<<crt->getSuprafata()<<" grame de frisca.\n";

    prajituri.push_back(crt);
}

vector<string> parse(string input, char delim) {
    vector<string> words;
    int i = input.find(delim, 0);
    int last = 0;
    while (i < input.size()) {
        if(i - last > 0){
            words.push_back(input.substr((unsigned int) last, (unsigned int) (i - last)));
        }
        last = i + 1;
        i = input.find(delim, (unsigned int) (i + 1));
    }

    if(input.length() - last > 0){
        words.push_back(input.substr((unsigned int) last, input.length() - last));
    }

    return words;
}

void Prajitura::run(istream& in, ostream& out) {

    do {
        string comanda;

        getline(cin, comanda);

        vector<string> input = parse(comanda, ' ');

        if(input.size() == 2 && input[0] == "ADD") {
            Forma* f = nullptr;
            if(input[1] == "cerc") f = new Cilindru;
            else if(input[1] == "triunghi") f = new Prisma;
            else if(input[1] == "patrat") f = new Patratic;
            else if(input[1] == "dreptunghi") f = new Paralelipiped;
            else out<<"Forma nerecunoscuta\n";

            if(f != nullptr) {
                f->citire(in, out);
                this->prajituri.push_back(f);
                out<<2 * f->getVolum()<<" g gem\n";
                out<<f->getSuprafata()<<" g frisca\n";
            }

        } else if(input.size() == 2 && input[0] == "REMOVE") {
            int a;
            istringstream(input[1].c_str()) >> a;

            if (a < prajituri.size()) {
                delete prajituri[a];
                prajituri.erase(prajituri.begin() + a);
            }

        } else if(input.size() == 1 && input[0] == "TOTAL" ) {

            float frisca = 0, gem = 0;

            for(Forma* f : prajituri) {
                frisca += f->getSuprafata();
                gem += 2 * f->getVolum();
            }

            out<<frisca<<" mg de frisca si "<<gem<<"mg gem\n";

        } else if(input.size() == 1 && input[0] == "STOP") {
            break;
        } else {
            out<<"comanda nerecunoscuta\n";
        }

    } while(true);
}

Prajitura::~Prajitura() {
    for(Forma* forma : prajituri) {
        delete forma;
    }
    prajituri.clear();
}