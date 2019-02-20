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
    int getLife();
    int getLifeFactor();

    void setStats(char, std::string, const int&, const int&, const int&, const int&, const int&, const int&);
    void virtual LoseLife(const int& eatCount);
    void virtual Growth(bool);
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
    int getFoliage();
    int getSeeds();
    void LoseLife(const int& eatCount);
    void Growth(bool);
};

class Seedless : public Plant
{

    public:
    
    Seedless(char, const int&, const int&);
    ~Seedless();
    void LoseLife();
};
#endif