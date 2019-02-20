#ifndef CLASSES_H
#define CLASSES_H
#include <iostream>
#include <list>
#include "plants.h"
#include "animals.h"

class tiles {
    //plant*
    //animals**
     char enviroment;

    public:

    tiles();
    // ~tiles();
    char getEnvironment();
    void setEnviroment(const char&);
};

class ecosystem {

    int terrainSize;
    int dayOfYear;
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
    point FindFreeTile();

    char findAnimal(const int&, const int&);
    char findPlant(const int&, const int&);

    void PrintAnimals();

    public:
    
    ecosystem(const int&, const int&);
    ~ecosystem();
    void RunEcosystem(const int&);
    void PrintSystem();
};
#endif