//
// Created by Lucian on 26/04/2017.
//

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
#include "ShipWar.h"
#include "Utilities.h"

bool operator==(const MyPoint& lhs, const MyPoint& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

void Ship::receiveAttack(int attackValue) {
    this->updateDamage(attackValue);
}

void Ship::doMaintenance() {
    this->updateFuel(-maintenanceCost);
}

void Ship::read(const map<string, string> &input) {
    this->position.x = Utilities::strToInt(input.at("x"));
//    cout<<"read\n";
    this->position.y = Utilities::strToInt(input.at("y"));
//    cout<<"read\n";
    this->rocketNr = Utilities::strToInt(input.at("racheteatac"));
}

unsigned int Ship::getId() {
    return this->id;
}

void Ship::setId(unsigned int id) {
    this->id = id;
}

Ship::~Ship() {
    cout<<"ma sterge\n";
    for(Action* action : actions) {
        delete action;
    }
}

Shape Ship::getShape() const {
    return shape;
}

void Ship::setShape(Shape shape) {
    Ship::shape = shape;
}

const MyPoint &Ship::getPosition() const {
    return position;
}

ActionResponse Ship::readShipCommand(istream &in) {
    // TODO: separa citirea pt client de procesarea din server
    cout<<Utilities::shapeToString(this->shape)<<" ("<<this->position.x<<" "<<this->position.y<<"): ";

    for(Action* action : this->actions) {
        cout<<action->getTypeString()<<" ";
    }

    string command;
    in>>command;

    Action* action;

    // TODO: verifica daca raspunsul e corect si se potriveste pe tipul de nava
    if(command == "Nothing") {
        action = new Nothing();
    } else if(command == "Attack") {
        action = new Attack();
    } else if(command == "Self_destroy") {
        action = new SelfDestroy();
    } else if(command == "Regenerate") {
        action = new Regenerate();
    } else {
        action = new Nothing();
    }

    cout<<endl;

    ActionResponse response = action->run(this, in);

    delete action;

    return response;
}

int Ship::getReceivedDamage() const {
    return receivedDamage;
}

void Ship::updateDamage(int damage) {
    this->damage += damage;
    if(this->damage >= 100) {
        this->isActive = false;
    }
}

void Ship::updateFuel(int fuel) {
    this->fuel += fuel;
    if(this->fuel <= 0) {
        this->isActive = false;
    }
}

bool Ship::isIsActive() const {
    return isActive;
}

void Salupa::paintTo(int table[SIZE][SIZE]) {
    cout<<"painting salupa\n";
    table[this->position.y][this->position.x] = this->id;
}

void Submarin::paintTo(int table[SIZE][SIZE]) {
    cout<<"painting submarin\n";
    for(int j = this->position.y; j < this->position.y + 2; j++) {
        table[j][this->position.x] = this->id;
//        cout<<"sub mark ";
    }
}

void Regenerable::regenerate() {
    this->updateDamage(-14);
    this->updateFuel(-5);
}

void Distrugator::paintTo(int table[SIZE][SIZE]) {
    cout<<"painting distrugator\n";
    for(int j = this->position.y; j < this->position.y + 3; j++) {
        table[j][this->position.x] = this->id;
    }
}

void Crucisator::receiveAttack(int attackValue) {

    bool rez = true;

    srand((unsigned int) time(0));

    int probability = hasShield ? rand() % 100 + 1 : 100;

    if(probability <= 75)
        rez = false;

    if(rez) {
        Ship::receiveAttack(attackValue);
    }
}

void Crucisator::paintTo(int table[SIZE][SIZE]) {
    cout<<"painting crucisator\n";
    for(int i = this->position.y; i < this->position.y + 3; i++) {
        for(int j = this->position.x; j < this->position.x + 2; j++) {
            table[i][j] = this->id;
        }
    }

    if(this->hasShield) {
        table[this->position.y + 1][this->position.x - 1] = this->id;
        table[this->position.y + 1][this->position.x + 2] = this->id;
    }
}

void Crucisator::read(const map<string, string> &input) {
    this->position.x = Utilities::strToInt(input.at("x"));
    this->position.y = Utilities::strToInt(input.at("y"));
    this->fuel = Utilities::strToInt(input.at("fuel"));
    this->rocketNr = Utilities::strToInt(input.at("racheteatac"));

//    for(auto rec : input) {
//        cout<<rec.first<<" ";
//    }

//    cout<<endl;
}

ActionResponse Crucisator::readShipCommand(istream &in) {
    ActionResponse response = Ship::readShipCommand(in);

    cout<<"Activati scutul? (Da/Nu) ";
    string ans;
    in>>ans;

    this->hasShield = ans == "Da";

    // TODO: marcheaza scutul pe tabla de joc

    return response;
}

void Server::startGame(istream& in) {

    bool redResp = true;
    bool blueResp = true;


    while(redResp && blueResp) {
        // invalidez tabla si o pregatesc pentru noul rand
        red.invalidate();
        blue.invalidate();

        list<ActionResponse> redActionResponses;
        list<ActionResponse> blueActionResponses;

        // parcurg navele jucatorilor si construiesc listele de actiuni pentru fiecare jucator
        for(auto shipRec : red.getShips()) {
            ActionResponse response = shipRec.second->readShipCommand(in);
            redActionResponses.push_back(response);
        }

        for(auto shipRec : blue.getShips()) {
            ActionResponse response = shipRec.second->readShipCommand(in);
            blueActionResponses.push_back(response);
        }

        // parcurg listele de actiuni pentru fiecare jucator si le interpretez
        for(ActionResponse resp : redActionResponses) {
            switch (resp.senderActionType) {
                case Actions::Nothing :
                    // doing nothing
                    break;
                case Actions::Self_destroy :
                    blue.handleSelfDestroy(resp.sender);
                    break;
                case Actions::Attack :
                    blue.handleAttack(resp.destination);
                    break;
                case Actions::Regenerate :
                    Regenerable* regenerable = dynamic_cast<Regenerable*>(resp.sender);
                    regenerable->regenerate();
                    break;
            }
        }

        for(ActionResponse resp : blueActionResponses) {
            switch (resp.senderActionType) {
                case Actions::Nothing :
                    // doing nothing
                    break;
                case Actions::Self_destroy :
                    red.handleSelfDestroy(resp.sender);
                    break;
                case Actions::Attack :
                    red.handleAttack(resp.destination);
                    break;
                case Actions::Regenerate :
                    Regenerable* regenerable = dynamic_cast<Regenerable*>(resp.sender);
                    regenerable->regenerate();
                    break;
            }
        }

        red.maintain();
        blue.maintain();

        redResp = red.clean();
        blueResp = blue.clean();
    }

    if(!(blueResp ^ redResp)) {
        cout<<"Remiza\n";
    } else if(blueResp) {
        cout<<"Albastru Castigator\n";
    } else {
        cout<<"Rosu Castigator\n";
    }

}

map<string, string> readCommand(string command) {
    map<string, string> myCommand;
    vector<string> components = Utilities::split(command, ';');
    for(string s : components) {
        vector<string> compPair = Utilities::split(s, ':');
        myCommand.insert(pair<string, string>(compPair[0], compPair[1]));
    }
    return myCommand;
};

void Server::parseInitCommand(string command) {

    map<string, string> myParsedCommand = readCommand(command);

    Board* board = myParsedCommand["player"] == "Rosu" ? &red : &blue;

    cout<<myParsedCommand["player"]<<endl;

    Ship* myShip;

    if(myParsedCommand["typeString"] == "SUBMARIN") {
        myShip = new Submarin;
    } else if(myParsedCommand["typeString"] == "CRUCISATOR") {
        myShip = new Crucisator;
    } else if(myParsedCommand["typeString"] == "DISTRUGATOR") {
        myShip = new Distrugator;
    } else {
        myShip = new Salupa;
    }

    myShip->read(myParsedCommand);

    board->addShip(myShip);
}

Board::Board() : shipId(0) {
}

void Board::invalidate() {
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            table[i][j] = 0;
        }
    }

    for(auto ship : ships) {
        cout<<"painting "<<ship.second->getId()<<" to the board\n";

        ship.second->paintTo(table);

        if(ship.second->getShape() == Shape::CRUCISATOR || ship.second->getShape() == Shape::CRUCISATOR_SCUT) {

            ship.second->setShape(Shape::CRUCISATOR);
            Crucisator* c = dynamic_cast<Crucisator*>(ship.second);
            c->setShield(false);
        }
    }
}

void Board::addShip(Ship *ship) {
    ship->setId(++this->shipId);
    this->ships.insert(pair<unsigned int, Ship*>(ship->getId(), ship));
}

Board::~Board() {
    cout<<"sterg tabla\n";

    for(auto rec : this->ships) {
        delete rec.second;
    }
}

void Board::print() {
    for(auto s : this->ships) {
        cout<<s.second->getId()<<" ";
    }
    cout<<endl;


    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            cout<<this->table[i][j];
        }
        cout<<endl;
    }
}

const map<unsigned int, Ship *> &Board::getShips() const {
    return ships;
}

void Board::handleSelfDestroy(Ship *ship) {
    int startX = ship->getPosition().x - 2 > 0 ? ship->getPosition().x - 2 : 0;
    int startY = ship->getPosition().y - 2 > 0 ? ship->getPosition().y - 2 : 0;

    for(int i = startY; i < startY + 6; i++) {
        for(int j = startX; j < startX + 5; j++) {
            if(ships.find((const unsigned int &) table[i][j]) != ships.end() && ships[table[i][j]]->isIsActive()) {
                ships[table[i][j]]->receiveAttack(100);
            }
        }
    }
}

void Board::handleAttack(const MyPoint &destination) {
    if(ships.find((const unsigned int &) table[destination.y][destination.x]) != ships.end() &&
        ships[table[destination.y][destination.x]]->isIsActive()) {
        ships[table[destination.y][destination.x]]->receiveAttack(ships[table[destination.y][destination.x]]->getReceivedDamage());
    }
}

bool Board::clean() {

    map<unsigned int, Ship*>::iterator itr = ships.begin();

    while(itr != ships.end()) {
        if(!itr->second->isIsActive()) {
            Ship* tmp = itr->second;
            ships.erase(itr++);
            delete tmp;
        } else {
            ++itr;
        }
    }

    return ships.size() != 0;
}

void Board::maintain() {
    for(auto shipRec : ships) {
        if(shipRec.second->isIsActive()) {
            shipRec.second->doMaintenance();
        }
    }
};

string Action::getTypeString() const {
    return typeString;
}

Actions Action::getActionType() const {
    return actionType;
}

Action::~Action() {
}

ActionResponse Nothing::run(Ship* sender, istream &in) {
    // doing nothing
    return ActionResponse(MyPoint{ -1, -1 }, sender, Actions::Nothing);
}

ActionResponse Attack::run(Ship* sender, istream &in) {
    // attacking
    MyPoint attackLocation;
    cout<<"Coordonatele tinta: (X, Y): ";
    in>>attackLocation.x>>attackLocation.y;

    return ActionResponse(attackLocation, sender, Actions::Attack);
}

ActionResponse SelfDestroy::run(Ship* sender, istream &in) {

    return ActionResponse(sender->getPosition(), sender, Actions::Self_destroy);
}

ActionResponse Regenerate::run(Ship *sender, istream &in) {
    return ActionResponse(MyPoint{ -3, -3}, sender, Actions::Regenerate);
}

ActionResponse::ActionResponse(const MyPoint &destination, Ship *sender, Actions senderActionType) : destination(
        destination), sender(sender), senderActionType(senderActionType) {}

void ActionResponse::print() {
    cout<<destination.x<<" "<<destination.y<<" "<<sender->getId()<<" "<<Utilities::shapeToString(sender->getShape())<<Utilities::actionToStrint(senderActionType)<<endl;
}




