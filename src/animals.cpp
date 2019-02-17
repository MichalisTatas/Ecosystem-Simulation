#include <iostream>
#include <string>
#include "../include/animals.h"

//////////////////////
//Animal's functions//
//////////////////////
Animal::Animal(){}
Animal::Animal(char mytoken, std::string myname, const int& mysize, const int& myspeed, bool myhibernates, bool mycanClimb, const int& x, const int& y)
    : token(mytoken), name(myname), size(mysize), speed(myspeed),hibernates(myhibernates), canClimb(mycanClimb)
{
    hungerCount = 0;
    eatenFood = 0;
    isAlive = true;
    isHungry = true;
    location.x = x; location.y = y;
    //eatcount
    //inHeat
    //inHibernation
}

Animal::~Animal(){}

std::string Animal::getName()
{
    return name;
}

int Animal::getSize()
{
    return size;
}

int Animal::getHungerCount()
{
    return hungerCount;
}

int Animal::getEatenFood()
{
    return eatenFood;
}

bool Animal::getIsAlive()
{
    return isAlive;
}

bool Animal::getIsHungry()
{
    return isHungry;
}

bool Animal::getInHeat(){
    return inHeat;
}

int Animal::getSpeed()
{
    return speed;
}

bool Animal::getHibernates()
{
    return hibernates;
}

bool Animal::getInHibernation()
{
    return inHibernation;
}

bool Animal::getCanClimb()
{
    return canClimb;
}

void Animal::setSize(){}//ovverride in child class?

void Animal::setHungerCount(const int& a)
{
    hungerCount = a;
}

void Animal::setEatenFood(const int& b)
{
    eatenFood = b;
}

void Animal::setIsAlive(const int& c)
{
    isAlive = false;
}

void Animal::setIsHungry(bool a)
{
    isHungry = a;
}

void Animal::setInHeat(bool b)
{
    inHeat = b;
}

void Animal::setSpeed(const int& d)
{
    speed = d;
}

void Animal::setInHibernation(bool c)
{
    inHibernation = c;
}

/////////////////////////
//Herbivore's functions//
/////////////////////////

Herbivore::Herbivore(char mytoken, const int& x, const int& y)
{
    switch(mytoken){
        case 'D':
            neededFood = 4;
            Animal('D', "Deer", 2, 4, false, false, x, y);
            break;
        case 'R':
            neededFood = 2;
            Animal('R', "Rabbit", 1, 2, false, false, x, y);
            break;
        case 'G':
            neededFood = 3;
            Animal('G', "Groundog", 2, 3, true, true, x, y);
            break;
        case 'S':
            neededFood = 1;
            Animal('S', "Salmon", 1, 5, false, false, x, y);
            break;
    }
}

Herbivore::~Herbivore(){}

int Herbivore::getNeededFood()
{
    return neededFood;
}

void Herbivore::setNeededFood(const int& e)
{
    neededFood = e;
}

/////////////////////////
//Carnivore's functions//
/////////////////////////

Carnivore::Carnivore(char mytoken, const int& x, const int& y)
{
    switch(mytoken){
        case 'F' :  attack = 1;
                    defence = 1;
                    Animal('F', "Fox", 1, 1, false, false, x, y);
        break;
        case 'W' :
                    attack = 2;
                    defence = 2;
                    Animal('W', "Wolf", 1, 2, false, false, x, y);
        break;
        case 'B' :
                    attack = 6;
                    defence = 6;
                    Animal('B', "Bear", 3, 4, true, false, x, y);
        break;
    }
}

Carnivore::~Carnivore(){}

int Carnivore::getAttack(){
    return attack;
}

int Carnivore::getDefence()
{
    return defence;
}

void Carnivore::setAttack(const int& f)
{
    attack = f;
}

void Carnivore::setDefence(const int& g)
{
    defence = g;
}