#include <iostream>
#include <string>

using namespace std;

class Plant
{
    protected:
    
    string name;
    int breedingProb;
    int illnessProb;
    int life;
    int lifeFactor;
    char token;
    //missing variable about plant's position
    
    public:
    
    Plant();
    Plant(char, string, const int&, const int&, const int&, const int&);
    ~Plant();
    //void set_name();
    //void set_token();
    int getBreedingProb();
    int getIllnessProb();
    int getLife();
    int getLifeFactor();
    void LoseLife();
    //missing function about returning plant's position
};

class Seeded : public Plant
{
    int foliage;
    int seeds;
    int size;

    public:

    Seeded(char);
    ~Seeded();
    int getFoliage();
    int getSeeds();
    void LoseSeeds();
    void LoseFoliage();
};

class Seedless : public Plant
{

    public:
    
    Seedless(char);
    ~Seedless();
};