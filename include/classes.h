#ifndef CLASSES_H
#define CLASSES_H
#include <iostream>
#include <list>
#include "plants.h"
#include "animals.h"

class tiles {
    char enviroment;
    bool hasPlant = false;
    //animals**

    public:

    tiles();
    bool getHasPlant();
    char getEnvironment();
    void setHasPLant(bool);
    void setEnviroment(const char&);
};

class ecosystem {

    int terrainSize;
    int dayOfYear;
    int growthPeriodPlants;
    int growthPeriodAnimals;
    int breedingRepPeriodPlants;
    int breedingRepPeriodHerbivore;
    int breedingRepPeriodCarnivore;
    tiles*** terrain;
    
    std::list<Seeded*> seededList;
    std::list<Seedless*> seedlessList;
    std::list<Herbivore*> herbivoreList;
    std::list<Carnivore*> carnivoreList;

    void MapGenerator();
    void GenerateRiver();
    void GenerateLake();
    void GenerateHills();
    void GenerateMeadow();
    void PlacePlants();
    void PlaceAnimals();

    void ApplySeason();
    void DailyReset();
    void AnimalMovement();
    void AnimalEating();
    void CheckDeadEntities();
    void CheckHunger();
    void AnimalBreeding();
    void PlantBreeding();
    point FindFreeTile(char, const int&, const int&);

    bool findHerbivore(const int&, const int&, const int& size, const int&);
    int findPLantToEat(const int&, const int&, char, const int&, int, bool);

    char findAnimal(const int&, const int&);
    char findPlant(const int&, const int&);
    void PrintAnimals();
    void PrintPlants();

    public:
    
    ecosystem(const int&, const int&);
    ~ecosystem();
    void RunEcosystem(const int&);
    void PrintSystem();
};
#endif