#ifndef PLANTS_H
#define PLANTS_H
#include "point.h"

class Plant
{
    std::string name;
    int life;
    int lifeFactor;
    int breedingProb;
    int illnessProb;
    char token;
    point location;
    
    public:
    
    Plant();
    Plant(char, std::string, const int&, const int&, const int&, const int&, const int&, const int&);
    ~Plant();
    char getToken();
    int getBreedingProb();
    int getIllnessProb();
    virtual int getLife();
    int getLifeFactor();
    int getPointX();
    int getPointY();

    void setStats(char, std::string, const int&, const int&, const int&, const int&, const int&, const int&);
    virtual void LoseLife(const int& eatCount);
    virtual void Growth();
    //missing function about returning plant's location
};

class Seeded : public Plant
{
    int foliage;
    int seeds;
    int size;

    public:

    Seeded(char, const int&, const int&);
    ~Seeded();
    int getLife();
    int getFoliage();
    int getSeeds();
    int getSize();
    void LoseLife(int);
    void Growth(bool);
};

class Seedless : public Plant
{

    public:
    
    Seedless(char, const int&, const int&);
    ~Seedless();
};
#endif