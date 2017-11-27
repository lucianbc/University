//
// Created by Lucian on 26/04/2017.
//

#ifndef RAZBOINAVAL_SHIPWAR_H
#define RAZBOINAVAL_SHIPWAR_H

#include <string>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

// Data Structures and Constants

const int SIZE = 15;

struct MyPoint {
    int x, y;
};

enum class Shape { SALUPA, SUBMARIN, DISTRUGATOR, CRUCISATOR, CRUCISATOR_SCUT };

enum class Actions { Nothing, Attack, Self_destroy, Regenerate };

// End Data Structures and Constants

// Start Game Model Classes

class Ship;

struct ActionResponse {
    MyPoint destination;
    Ship* sender;
    Actions senderActionType;

    ActionResponse(const MyPoint &destination, Ship *sender, Actions senderActionType);

    void print();
};

class Action {
protected:
    string typeString;
    Actions actionType;
public:
    virtual ActionResponse run(Ship* sender, istream &in) = 0;
    string getTypeString() const;
    Actions getActionType() const;

    virtual ~Action();
};

class Nothing : public Action {
public:
    Nothing() {
        this->typeString = "Nothing";
        this->actionType = Actions::Nothing;
    }

    ActionResponse run(Ship* sender, istream &in) override;
};

class Attack : public Action {
public:
    Attack() {
        this->typeString = "Attack";
        this->actionType = Actions::Attack;
    }

    ActionResponse run(Ship* sender, istream &in) override;
};

class SelfDestroy : public Action {
public:
    SelfDestroy() {
        this->typeString = "Self_destroy";
        this->actionType = Actions::Self_destroy;
    }

    ActionResponse run(Ship* sender, istream &in) override ;
};

class Regenerate : public Action {
public:
    Regenerate() {
        this->typeString = "Regenerate";
        this->actionType = Actions::Regenerate;
    }

    ActionResponse run(Ship* sender, istream &in) override;
};

class Ship {
protected:
    unsigned int id;
    bool isActive;
    Shape shape;
    MyPoint position;
    int rocketNr;
    int damage;
    int fuel;
    int receivedDamage;
    int maintenanceCost;
//    Action* actions[];
    vector<Action*> actions;

public:
    Shape getShape() const;

    void setShape(Shape shape);

    virtual void receiveAttack(int attackValue);
    virtual void doMaintenance();
    virtual void paintTo(int table[SIZE][SIZE]) = 0;
    virtual void read(const map<string, string> &input);
    virtual ActionResponse readShipCommand(istream &in);


    Ship(unsigned int id, const MyPoint &position, int rocketNr) : id(id), isActive(true), position(position), damage(0), rocketNr(rocketNr) {}

    Ship() : isActive(true), damage(0) {}

    void setId(unsigned int id);

    bool isIsActive() const;

    void updateDamage(int damage);

    void updateFuel(int fuel);

    const MyPoint &getPosition() const;

    unsigned int getId();

    int getReceivedDamage() const;

    virtual ~Ship();
};

class Salupa : public Ship {

private:
    void init() {
        this->shape = Shape::SALUPA;
        this->fuel = 55;
        this->receivedDamage = 100;
        this->maintenanceCost = 1;
        this->actions.push_back(new Nothing());
        this->actions.push_back(new Attack());
    }

public:
    Salupa(unsigned int id, const MyPoint &position, int rocketNr) : Ship(id, position, rocketNr) {
        init();
    }

    Salupa() : Ship() {
        init();
    }

    void paintTo(int table[SIZE][SIZE]) override;
};

class Submarin : public Ship {
private:
    void init() {
        this->shape = Shape::SUBMARIN;
        this->fuel = 225;
        this->receivedDamage = 50;
        this->maintenanceCost = 2;
//        this->actions = { Actions::Nothing, Actions::Attack, Actions::Self_destroy };
        this->actions.push_back(new Nothing());
        this->actions.push_back(new Attack());
        this->actions.push_back(new SelfDestroy());
    }
public:
    Submarin(unsigned int id, const MyPoint &position, int rocketNr) : Ship(id, position, rocketNr) {
        init();
    }

    Submarin() : Ship() {
        init();
    }

    void paintTo(int table[SIZE][SIZE]) override;
};

class Regenerable : public Ship {
public:
    virtual void regenerate();

    Regenerable() : Ship() {}

    Regenerable(unsigned int id, const MyPoint &position, int rocketNr) : Ship(id, position, rocketNr) {}
};

class Distrugator : public Regenerable {
private:
    void init() {
        this->shape = Shape::DISTRUGATOR;
        this->fuel = 300;
        this->receivedDamage = 35;
        this->maintenanceCost = 3;
//        this->actions = { Actions::Nothing, Actions::Attack, Actions::Regenerate };
        this->actions.push_back(new Nothing());
        this->actions.push_back(new Attack());
        this->actions.push_back(new Regenerate());
    }

public:
    Distrugator(unsigned int id, const MyPoint &position, int rocketNr) : Regenerable(id, position, rocketNr) {
        init();
    }

    Distrugator() : Regenerable() {
        init();
    }

    void paintTo(int table[SIZE][SIZE]) override;
};

class Crucisator : public Regenerable {
private:
    bool hasShield;

    void init() {
        this->shape = Shape::CRUCISATOR;
        this->fuel = fuel;
        this->receivedDamage = 20;
        this->maintenanceCost = 6;
        this->hasShield = false;
//        this->actions = { Actions::Nothing, Actions::Attack, Actions::Regenerate };
        this->actions.push_back(new Nothing());
        this->actions.push_back(new Attack());
        this->actions.push_back(new Regenerate());
    }

public:
    Crucisator(unsigned int id, const MyPoint &position, int rocketNr, int fuel) : Regenerable(id, position, rocketNr) {
        init();
    }

    Crucisator() : Regenerable() {
        init();
    }

    bool getShield() { return hasShield; }

    void setShield(bool shield) { this->hasShield = shield; }

    void receiveAttack(int attackValue) override;

    void paintTo(int table[SIZE][SIZE]) override;

    void read(const map<string, string> &input) override;

    ActionResponse readShipCommand(istream &in) override;
};

// End Game Model Classes

// Start Board

class Board {
private:
    unsigned int shipId;

    int table[SIZE][SIZE];

    map<unsigned int, Ship*> ships;

public:
    Board();

    void invalidate();

    void addShip(Ship *ship);

    virtual ~Board();

    const map<unsigned int, Ship *> &getShips() const;

    void handleSelfDestroy(Ship* ship);

    void handleAttack(const MyPoint &destination);

    void print();

    void maintain();

    // returneaza true daca mai sunt nave, altfel fals
    bool clean();
};

// End Board

// Start Game Server

class Server {
private:
    Board red, blue;

public:
    void parseInitCommand(string command);
    void startGame(istream &in);
};

// End Game Server



#endif //RAZBOINAVAL_SHIPWAR_H
