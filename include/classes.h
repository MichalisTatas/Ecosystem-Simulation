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
    char getEnviroment();
    void setEnviroment(const char&);
};

class ecosystem {

    int terrainSize;
    int dayOfYear;
    tiles*** terrain;
    
    std::list<Seeded> seededList;
    std::list<Seedless> seedlessList;
    //animals list

    void MapGenerator();
    void GenerateRiver();
    void GenerateLake();
    void GenerateHills();
    void GenerateMeadow();
    void PlacePlants();
    //void PlaceAnimals();

    public:
    
    ecosystem(const int&, const int&);
    ~ecosystem();
    // void RunEcosystem();
    void PrintSystem();
};