#include <iostream>
#include <string>
#include "../include/animals.h"

using namespace std;

//////////////////////
//Animal's functions//
//////////////////////
Animal::Animal(){}
Animal::Animal(char mytoken, string myname,int mysize,int myspeed,bool myhibernates,bool mycanClimb)
    : token(mytoken), name(myname), size(mysize), speed(myspeed),hibernates(myhibernates), canClimb(mycanClimb)
{
    hungerCount = 0;
    eatenFood = 0;
    //eatcount
    isAlive = true;
    isHungry = true;
    //inHeat
    //inHibernation
}

Animal::~Animal(){}

string Animal::getName(){
    return name;
}

void Animal::setSize(){}//ovverride in child class?

int Animal::getSize(){
    return size;
}

void Animal::setHungerCount(int a){
    hungerCount = a;
}

int Animal::getHungerCount(){
    return hungerCount;
}

void Animal::setEatenFood(int b){
    eatenFood = b;
}

int Animal::getEatenFood(){
    return eatenFood;
}

void Animal::setIsAlive(int c){
    isAlive = false;
}

bool Animal::getIsAlive(){
    return isAlive;
}

void Animal::setIsHungry(bool a){
    isHungry = a;
}

bool Animal::getIsHungry(){
    return isHungry;
}

void Animal::setInHeat(bool b){
    inHeat = b;
}

bool Animal::getInHeat(){
    return inHeat;
}

void Animal::setSpeed(int d){
    speed = d;
}

int Animal::getSpeed(){
    return speed;
}

bool Animal::getHibernates(){
    return hibernates;
}

void Animal::setInHibernation(bool c){
    inHibernation = c;
}

bool Animal::getInHibernation(){
    return inHibernation;
}

bool Animal::getCanClimb(){
    return canClimb;
}

/////////////////////////
//Herbivore's functions//
/////////////////////////

Herbivore::Herbivore(char mytoken){
    switch(mytoken){
        case 'D' :  neededFood = 4;
                    Animal('D',"Deer",2,4,false,false);
        break;
        case 'R' :  neededFood = 2;
                    Animal('R',"Rabbit",1,2,false,false);
        break;
        case 'G' :  neededFood = 3;
                    Animal('G',"Groundog",2,3,true,true);
        break;
        case 'S' :  neededFood = 1;
                    Animal('S',"Salmon",1,5,false,false);
        break;
    }
}

Herbivore::~Herbivore(){}

void Herbivore::setNeededFood(int e){
    neededFood = e;
}

int Herbivore::getNeededFood(){
    return neededFood;
}

/////////////////////////
//Carnivore's functions//
/////////////////////////

Carnivore::Carnivore(char mytoken){
    switch(mytoken){
        case 'F' :  attack = 1;
                    defence = 1;
                    Animal('F',"Fox",1,1,false,false);
        break;
        case 'W' :
                    attack = 2;
                    defence = 2;
                    Animal('W',"Wolf",1,2,false,false);
        break;
        case 'B' :
                    attack = 6;
                    defence = 6;
                    Animal('B',"Bear",3,4,true,false);
        break;
    }
}

Carnivore::~Carnivore(){}

void Carnivore::setAttack(int f){
    attack = f;
}

int Carnivore::getAttack(){
    return attack;
}

void Carnivore::setDefence(int g){
    defence = g;
}

int Carnivore::getDefence(){
    return defence;
}