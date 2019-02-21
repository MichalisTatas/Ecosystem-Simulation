#include <iostream>
#include <string>
#include "../include/classes.h"

//////////////////////
//Animal's functions//
//////////////////////
Animal::Animal() {}
Animal::Animal(char mytoken, std::string myname, const int& mysize, const int& myspeed, bool myhibernates, bool mycanClimb, const int& x, const int& y)
    : token(mytoken), name(myname), size(mysize), speed(myspeed),hibernates(myhibernates), canClimb(mycanClimb), hungerCount(0), eatenFood(0), isAlive(true), isHungry(true)
{
    std::cout << x << " " << y << std::endl;
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

void Animal::setStats(char mytoken, std::string myname, const int& mysize, const int& myspeed, bool myhibernates, bool mycanClimb, const int& x, const int& y)
{
    token = mytoken; name = myname; size = mysize; speed = myspeed;
    hibernates = myhibernates; canClimb = mycanClimb; location.x = x; location.y = y;
}

void Animal::setSize(const int&m)
{
    size = size + m;
}

void Animal::setHungerCount(const int& a)
{
    hungerCount = a;
}

void Animal::setEatenFood(const int& b)
{
    eatenFood = b;
}

void Animal::Kill()
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
    speed = speed + d;
}

void Animal::setInHibernation(bool c)
{
    inHibernation = c;
}

void Animal::setPointX(bool a){
    if(a) location.x = location.x + 1;
    else location.x = location.x - 1;
}

int Animal::getPointX(){
    return location.x;
}

void Animal::setPointY(bool a){
    if(a) location.y = location.y + 1;
    else location.y = location.y - 1;
}

int Animal::getPointY(){
    return location.y;
}

char Animal::getToken(){
    return token;
}

/////////////////////////
//Herbivore's functions//
/////////////////////////

Herbivore::Herbivore(char mytoken, const int& x, const int& y)
{
    switch(mytoken){
        case 'D':
            neededFood = 4;
            setStats('D', "Deer", 2, 4, false, false, x, y);
            break;
        case 'R':
            neededFood = 2;
            setStats('R', "Rabbit", 1, 2, false, false, x, y);
            break;
        case 'G':
            neededFood = 3;
            setStats('G', "Groundog", 2, 3, true, true, x, y);
            break;
        case 'S':
            neededFood = 1;
            setStats('S', "Salmon", 1, 5, false, false, x, y);
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
    neededFood = neededFood + e;
}

void Herbivore::Raise(){
    switch(getToken()){
        case 'D' :  if(getSize()<5) setSize(1);
                    if(getSpeed()<8) setSpeed(2);
                    if(getNeededFood()<8) setNeededFood(2);
        break;
        case 'R' :  if(getSize()<2) setSize(1);
                    if(getSpeed()<6) setSpeed(2);
                    if(getNeededFood()<4) setNeededFood(1); 
        break;
        case 'G' :  if(getSize()<3) setSize(1);
                    if(getSpeed()<5) setSpeed(1);
                    if(getNeededFood()<5) setNeededFood(1);
        break;
        //dont need case for salmon bcz its already adult since birth
    }
}

void Herbivore::Move(int terrainSize, tiles*** terrain){
    switch(getToken()){
        case 'D' :
            for(int i=0; i<getSpeed(); ) {
                switch(rand()%4) {
                    case 0: //right
                        if(getPointX() < terrainSize-1) {
                            setPointX(true);
                            i++;
                        }
                        break;
                    case 1:
                        if(getPointX() > 0) {
                            setPointX(false);
                            i++;
                        }
                        break;
                    case 2:
                        if(getPointY() < terrainSize-1) {
                            setPointY(true);
                            i++;
                        }
                        break;
                    case 3:
                        if(getPointY() > 0) {
                            setPointY(false);
                            i++;
                        }
                        break;
                }
            }
    break;
    case 'R' :
        for(int i=0; i<getSpeed();){
            switch(rand()%4){
                case 0 :    if(getPointX() < terrainSize-1) {
                                if(terrain[getPointX()+1][getPointY()]->getEnvironment() != '^') {
                                    setPointX(true);
                                    i++;
                                }
                            }
                break;
                case 1 :    if(getPointX() > 0){
                                if(terrain[getPointX()-1][getPointY()]->getEnvironment() != '^') {
                                    setPointX(false);
                                    i++;
                                }
                            }
                break;
                case 2 :    if(getPointY() < terrainSize-1) {
                                if(terrain[getPointX()][getPointY()+1]->getEnvironment() != '^') {
                                    setPointY(true);
                                    i++;
                                }
                            }
                break;
                case 3 :    if(getPointY() > 0) {
                                if(terrain[getPointX()][getPointY()-1]->getEnvironment() != '^') {
                                    setPointY(false);
                                    i++;
                                }
                            }
                break;
            }
        }
        break;
    case 'G' :
        for(int i=0; i<getSpeed();){
            switch(rand()%4){
                case 0 :    if(getPointX() < terrainSize-1) {
                                if(terrain[getPointX()+1][getPointY()]->getEnvironment() != '#') {
                                    setPointX(true);
                                    i++;
                                }
                            }
                break;
                case 1 :    if(getPointX() > 0) {
                                if(terrain[getPointX()-1][getPointY()]->getEnvironment() != '#') {
                                    setPointX(false);
                                    i++;
                                }
                            }
                break;
                case 2 :    if(getPointY() < terrainSize-1) {
                                if(terrain[getPointX()][getPointY()+1]->getEnvironment() != '#') {
                                    setPointY(true);
                                    i++;
                                }
                            }
                break;
                case 3 :    if(getPointY() > 0) {
                                if(terrain[getPointX()][getPointY()-1]->getEnvironment() != '#') {
                                    setPointY(false);
                                    i++;
                                }
                            }
                break;
            }
        }
        break;
    case 'S' :
        for(int i=0; i<getSpeed();){
            switch(rand()%4){
                case 0 :    if(getPointX() < terrainSize-1) {
                                if(terrain[getPointX()+1][getPointY()]->getEnvironment() == '#') {
                                    setPointX(true);
                                    i++;
                                }
                            }
                break;
                case 1 :    if(getPointX() > 0) {
                                if(terrain[getPointX()-1][getPointY()]->getEnvironment() == '#') {
                                    setPointX(false);
                                    i++;
                                }
                            }
                break;
                case 2 :    if(getPointY() < terrainSize-1) {
                                if(terrain[getPointX()][getPointY()+1]->getEnvironment() == '#') {
                                    setPointY(true);
                                    i++;
                                }
                            }
                break;
                case 3 :    if(getPointY() > 0) {
                                if(terrain[getPointX()][getPointY()-1]->getEnvironment() == '#') {
                                    setPointY(false);
                                    i++;
                                }
                            }
                break;
            }
        }
        break;
}
}
/////////////////////////
//Carnivore's functions//
/////////////////////////

Carnivore::Carnivore(char mytoken, const int& x, const int& y)
{
    switch(mytoken){
        case 'F' :  attack = 1;
                    defence = 1;
                    setStats('F', "Fox", 1, 1, false, false, x, y);
        break;
        case 'W' :
                    attack = 2;
                    defence = 2;
                    setStats('W', "Wolf", 1, 2, false, false, x, y);
        break;
        case 'B' :
                    attack = 6;
                    defence = 6;
                    setStats('B', "Bear", 3, 4, true, false, x, y);
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
    attack = attack + f;
}

void Carnivore::setDefence(const int& g)
{
    defence = defence + g;
}

void Carnivore::Raise(){
    switch(getToken()){
        case 'F' :  if(getSize()<4) setSize(1);
                    if(getAttack()<5) setAttack(1);
                    if(getDefence()<5) setDefence(1);
                    if(getSpeed()<6) setSpeed(1);
                    //get needed food?
        break;
        case 'W' :  if(getSize()<7) setSize(1);
                    if(getAttack()<8) setAttack(2);
                    if(getDefence()<6) setDefence(2);
                    if(getSpeed()<8) setSpeed(2);
                    //get needed food?
        break;
        case 'B' :  if(getSize()<10)    
                        if(getSize()==9) setSize(1);
                        else setSize(2);
                    if(getAttack()<10) setAttack(2);
                    if(getDefence()<10) setDefence(2);
                    if(getSpeed()<4) setSpeed(2);
                    //get needed food?
        break;
    }
}

void Carnivore::Move(int terrainSize) {
    for(int i=0; i<getSpeed(); ) {
        switch(rand()%4){
            case 0 :    if(getPointX() < terrainSize-1) {
                            setPointX(true);
                            i++;
                        }
            break;
            case 1 :    if(getPointX() > 0) {
                            setPointX(false);
                            i++;
                        }
            break;
            case 2 :    if(getPointY() < terrainSize-1) {
                            setPointY(true);
                            i++;
                        }
            break;
            case 3 :    if(getPointY() > 0) {
                            setPointY(false);
                            i++;
                        }
            break;
        }
    }
}