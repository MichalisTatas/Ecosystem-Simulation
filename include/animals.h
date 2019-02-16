#include <iostream>
#include <string>
using namespace std;

class Animal{
protected:
    string name;
    char token;
    int size;
    int hungerCount;              //how long it has been since the animal ate
    int eatenFood;
    int eatCount;
    //current location?
    bool isAlive;
    bool isHungry;
    bool inHeat;
    int speed;
    bool hibernates;
    bool inHibernation;
    bool canClimb;
public:
    Animal();
    Animal(char, string, int, int, bool, bool);
    ~Animal();
    string getName();
    void setSize();
    int getSize();
    void setHungerCount(int a);
    int getHungerCount();        
    void setEatenFood(int b);
    int getEatenFood();
    void setIsAlive(int c);
    bool getIsAlive();
    void setIsHungry(bool a);
    bool getIsHungry();
    void setInHeat(bool b);
    bool getInHeat();
    void setSpeed(int d);
    int getSpeed();
    bool getHibernates();
    void setInHibernation(bool c);
    bool getInHibernation();
    bool getCanClimb();
};

class Herbivore : public Animal{
private:
    int neededFood;
public:
    Herbivore(char);
    ~Herbivore();
    bool getCanClimb();
    void setNeededFood(int e);
    int getNeededFood();
};

class Carnivore : public Animal{
private:
    int attack;
    int defence;
public:
    Carnivore(char);
    ~Carnivore();
    void setAttack(int f);
    int getAttack();
    void setDefence(int g);
    int getDefence();
};