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
    int hungerCount = 0;              //how long it has been since the animal ate
    int eatenFood = 0;
    int eatCount = 0;
    point location;
    bool isAlive = true;
    bool isHungry = true;
    bool inHeat;
    int speed;
    bool hibernates;
    bool inHibernation;
    bool canClimb;
    
    public:

    Animal();
    Animal(char, std::string, const int&, const int&, bool, bool, const int&, const int&);
    virtual ~Animal();
    char getToken();
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
    int getPointX();
    int getPointY();

    void setStats(char, std::string, const int&, const int&, bool, bool, const int&, const int&);
    virtual void eloBoost();
    void setSize(const int&);
    void setHungerCount(const int&);
    void setEatenFood(const int&);
    void Kill();
    void setIsHungry(bool);
    void setInHeat(bool);
    void setSpeed(const int&);
    void setInHibernation(bool);
    void setPointX(bool);
    void setPointY(bool);
};

class Herbivore : public Animal
{
    int neededFood;
    int eatMax;

    public:

    Herbivore(char, const int&, const int&);
    ~Herbivore();
    int getNeededFood();
    int getEatMax();
    void eloBoost();
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