#ifndef ANIMALS_H
#define ANIMALS_H
#include <iostream>
#include <string>
#include "point.h"
// #include "classes.h"

class tiles;
class ecosystem;

class Animal
{
    std::string name;
    char token;
    int size;
    int hungerCount;              //how long it has been since the animal ate
    int eatenFood;
    int eatCount;
    point location;
    bool isAlive;
    bool isHungry;
    bool inHeat;
    int speed;
    bool hibernates;
    bool inHibernation;
    bool canClimb;
    
    public:

    Animal();
    Animal(char, std::string, const int&, const int&, bool, bool, const int&, const int&);
    ~Animal();
    std::string getName();
    int getSize();
    int getHungerCount();
    int getEatenFood();
    bool getIsAlive();
    bool getIsHungry();
    bool getInHeat();
    int getSpeed();
    bool getHibernates();
    bool getInHibernation();
    bool getCanClimb();
    

    void setStats(char, std::string, const int&, const int&, bool, bool, const int&, const int&);
    void setSize(const int&);
    void setHungerCount(const int&);
    void setEatenFood(const int&);
    void setIsAlive(const int&);
    void setIsHungry(bool);
    void setInHeat(bool);
    void setSpeed(const int&);
    void setInHibernation(bool);
    void setPointX(int);
    int getPointX();
    void setPointY(int);
    int getPointY();
    char getToken();

};

class Herbivore : public Animal
{
    int neededFood;

    public:

    Herbivore(char, const int&, const int&);
    ~Herbivore();
    int getNeededFood();
    void setNeededFood(const int&);
    void Move(int terrainSize, tiles***);
    void Raise();
};

class Carnivore : public Animal
{
    int attack;
    int defence;
    
    public:

    Carnivore(char, const int&, const int&);
    ~Carnivore();
    int getAttack();
    int getDefence();
    void setAttack(const int&);
    void setDefence(const int&);
    void Move(int terainSize);
    void Raise();
};
#endif