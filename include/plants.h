#include "point.h"

class Plant
{
    std::string name;
    int life;
    int lifeFactor;
    int breedingProb;
    int illnessProb;
    char token;
    point position;
    
    public:
    
    Plant();
    Plant(char, std::string, const int&, const int&, const int&, const int&, const int&, const int&);
    ~Plant();
    //void set_name();
    //void set_token();
    int getBreedingProb();
    int getIllnessProb();
    int getLife();
    int getLifeFactor();
    void virtual LoseLife(const int& eatCount);
    void virtual Growth(bool);
    //missing function about returning plant's position
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