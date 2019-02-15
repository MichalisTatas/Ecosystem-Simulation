#include <iostream>
#include <string>
using namespace std;

class Plant{
protected:
    string name;
    char token;
    int breedingProb;
    int illnessProb;
    int life;
    int lifeFactor;
    //missing variable about plant's position
public:
    Plant();
    Plant(char, string, int, int, int, int);
    ~Plant();
    //void set_name();
    //void set_token();
    int get_breedingProb();
    int get_illnessProb();
    int get_life();
    int get_lifeFactor();
    void LoseLife();
    //missing function about returning plant's position
};

class SeededPlant : public Plant{
    int foliage;
    int seeds;
    int size;
    public:
    SeededPlant(char mytoken);
    ~SeededPlant();
    int get_foliage();
    int get_seeds();
    void LoseSeeds();
    void LoseFoliage();
};

class SeedlessPlant : public Plant{

public:
    SeedlessPlant(char mytoken);
    ~SeedlessPlant();
};