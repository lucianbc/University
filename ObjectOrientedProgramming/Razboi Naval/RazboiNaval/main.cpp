#include <iostream>
#include <fstream>
#include "Utilities.h"
#include "ShipWar.h"

using namespace std;

int main() {

    Server gameServer;

    // format input acceptat:
    // player:value;typeString:value;x:value;y:value;racheteatac:value;fuel:value
    // fuel se aplica numai pentru crucisator

    string st = "player:Rosu;typeString:SUBMARIN;x:0;y:1;racheteatac:10|player:Albastru;typeString:CRUCISATOR;x:1;y:2;racheteatac:30;fuel:500;|player:Rosu;typeString:CRUCISATOR;x:1;y:6;racheteatac:20;fuel:400;|player:Albastru;typeString:DISTRUGATOR;x:10;y:6;racheteatac:10;";

    vector<string> v = Utilities::split(st, '|');

    for(string s : v) {
        gameServer.parseInitCommand(s);
    }

    ifstream fin("input.in");

    gameServer.startGame(cin);

//    Ship* myShip = new Salupa;
//
//    delete myShip;

    return 0;
}