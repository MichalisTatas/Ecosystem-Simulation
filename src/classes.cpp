#include <iostream>
#include <cstdlib>
#include <list>
// #include <iterator>
#include "../include/classes.h"

using namespace std;

tiles::tiles()
    : enviroment('0')
{

}

char tiles::getEnvironment()
{
    return enviroment;
}

void tiles::setEnviroment(const char& ch)
{
    enviroment = ch;
}

ecosystem::ecosystem(const int& tSize, const int& dOfYear)
    :terrainSize(tSize), dayOfYear(dOfYear)
{
    std::cout << "Generating Terrain..." << std::endl;
    MapGenerator();
    GenerateRiver();
    GenerateLake();
    GenerateHills();
    GenerateMeadow();
    std::cout << "Terrain Generated!" << std::endl << "Generating Life..." << std::endl;
    PlacePlants();
    PlaceAnimals();
    std::cout << "Life Generated!" << std::endl << "Ecosystem ready for simulation" << std::endl;
}

ecosystem::~ecosystem()
{
    for(int i=0; i < terrainSize; i++) {
        for(int j=0; j < terrainSize; j++) {
            delete[] terrain[i][j];
        }
        delete[] terrain[i];
    }
    delete[] terrain;
}

void ecosystem::MapGenerator()
{    
    terrain = new tiles**[terrainSize];
    for(int i=0; i < terrainSize; i++) {
        terrain[i] = new tiles*[terrainSize];
        for(int j=0; j < terrainSize; j++) {
            terrain[i][j] = new tiles();
        }
    }
    std::cout << "Map Generated" << std::endl;
}

void ecosystem::GenerateRiver()
{
    int x=0, y= 5 + rand()%(terrainSize-10);
    terrain[x][y]->setEnviroment('#');
    while(x < terrainSize-1) {
        if(rand()%10 < 3) {
            switch (rand()%4)
            {
                case 0:
                    if(y < terrainSize-1) {
                        terrain[x][++y]->setEnviroment('#');
                        terrain[++x][y]->setEnviroment('#');
                    }
                    break;
                case 1:
                    if(y < terrainSize-2) {
                        terrain[x][++y]->setEnviroment('#');
                        terrain[x][++y]->setEnviroment('#');
                        terrain[++x][y]->setEnviroment('#');
                    }
                    break;
                case 2:
                    if(y > 0) {
                        terrain[x][--y]->setEnviroment('#');
                        terrain[++x][y]->setEnviroment('#');
                    }
                    break;
                case 3:
                    if(y > 1) {
                        terrain[x][--y]->setEnviroment('#');
                        terrain[x][--y]->setEnviroment('#');
                        terrain[++x][y]->setEnviroment('#');
                    }
                    break;
                default:
                    terrain[++x][y]->setEnviroment('#');
                    break;
            }
        }
        else {
            terrain[++x][y]->setEnviroment('#');
        }
    }
    std::cout << "River Generated" << std::endl;
}

void ecosystem::GenerateLake()
{
    int lakeSize=terrainSize/3, x=rand()%(terrainSize-lakeSize+1), y=rand()%(terrainSize-lakeSize+1), joker=y;

    for(int i=0; i < lakeSize; i++) {
        for(int j=0; j < lakeSize; j++) {
            terrain[x][y++]->setEnviroment('#');
        }
        y=joker; x++;
    }
    std::cout << "Lake Generated" << std::endl;
}

void ecosystem::GenerateHills()
{
    int size, hills=terrainSize/5, x = rand()%(terrainSize-hills), y = rand()%(terrainSize-hills), joker=y;
    bool cleanGrount = true;

    for(int count=0; count < hills; ) {
        size = (rand()%3)+2;
        cleanGrount = true;

        for(int i=0; i < size; i++) {
            for(int j=0; j < size; j++) {
                if(terrain[x][y++]->getEnvironment() != '0') {
                    cleanGrount = false;
                }
            }
            y = joker; x++;
        }
        if(cleanGrount) {
            for(int i=0; i < size; i++) {
                x--;
                for( int j=0; j < size; j++) {
                    terrain[x][y++]->setEnviroment('^');
                }
                y = joker;
            }
            count++;
            x = rand()%(terrainSize-hills);
            y = rand()%(terrainSize-hills);
            joker = y;
        }
        else {
            x = rand()%(terrainSize-hills);
            y = rand()%(terrainSize-hills);
            joker = y;
        }
    }
    std::cout << "Hills Generated" << std::endl;
}

void ecosystem::GenerateMeadow()
{
    for(int i=0; i < terrainSize; i++) {
        for(int j=0; j < terrainSize; j++) {
            if(terrain[i][j]->getEnvironment()!='#' && terrain[i][j]->getEnvironment()!='^') {
                terrain[i][j]->setEnviroment('"');
            }
        }
    }
    std::cout << "Meadow Generated" << std::endl;
}

void ecosystem::PlacePlants()
{
    Seeded* seededPlant;
    Seedless* seedlessPlant;

    for(int x=0; x < terrainSize; x++) {
        for(int y=0; y < terrainSize; y++) {
            if(rand()%10 < 3) {
                switch (terrain[x][y]->getEnvironment()) {
                    case '"':
                        switch (rand()%3) {
                            case 1: {
                                seededPlant = new Seeded('M', x, y);
                                seededList.push_back(seededPlant);
                                break;
                            }
                            case 2: {
                                seededPlant = new Seeded('O', x, y);
                                seededList.push_back(seededPlant);
                                break;
                            }
                            default:
                                seedlessPlant = new Seedless('G', x, y);
                                seedlessList.push_back(seedlessPlant);
                                break;
                        }
                        break;
                    case '^':
                        switch (rand()%2) {
                            case 1: {
                                seededPlant = new Seeded('M', x, y);
                                seededList.push_back(seededPlant);
                                break;
                            }
                            default:
                                seededPlant = new Seeded('P', x, y);
                                seededList.push_back(seededPlant);
                                break;
                        }
                        break;
                    default:
                        seedlessPlant = new Seedless('A', x, y);
                        seedlessList.push_back(seedlessPlant);
                        break;
                }
            }
        }
    }
}

void ecosystem::PlaceAnimals()
{
    Herbivore* herbivoreAnimal;
    Carnivore* carnivoreAnimal;

    for(int x=0; x < terrainSize; x++) {
        for(int y=0; y < terrainSize; y++) {
            if(rand()%10 < 4) {
                switch (terrain[x][y]->getEnvironment()) {
                    case '"':
                        switch (rand()%5) {
                            case 0: {
                                herbivoreAnimal = new Herbivore('D', x, y);
                                herbivoreList.push_back(herbivoreAnimal);
                                break;
                            }
                            case 1: {
                                herbivoreAnimal = new Herbivore('R', x, y);
                                herbivoreList.push_back(herbivoreAnimal);
                                break;
                            }
                            case 2: {
                                herbivoreAnimal = new Herbivore('G', x, y);
                                herbivoreList.push_back(herbivoreAnimal);
                                break;
                            }
                            case 3: {
                                carnivoreAnimal = new Carnivore('F', x, y);
                                carnivoreList.push_back(carnivoreAnimal);
                                break;
                            }
                            default:
                                carnivoreAnimal = new Carnivore('W', x, y);
                                carnivoreList.push_back(carnivoreAnimal);
                                break;
                        }
                        break;
                    case '^':
                        switch (rand()%2) {
                            case 0: {
                                carnivoreAnimal = new Carnivore('W', x, y);
                                carnivoreList.push_back(carnivoreAnimal);
                                break;
                            }
                            default:
                                carnivoreAnimal = new Carnivore('B', x, y);
                                carnivoreList.push_back(carnivoreAnimal);
                                break;
                        }
                        break;
                    default:
                        herbivoreAnimal = new Herbivore('S', x, y);
                        herbivoreList.push_back(herbivoreAnimal);
                        break;
                }
            }
        }
    }
}
void ecosystem::RunEcosystem(const int& numberOdDays)
{
    for(int i=0; i < numberOdDays; i++) {
        ApplySeason();
        DailyReset();
        for(int j=0; j < 24; j++) {
            AnimalMovement();
            // AnimalEating();
        }
        CheckHunger();
        CheckDeadEntities();
        // AnimalBreeding();
        // PlantBreeding();
        PrintAnimals();
    }
}

void ecosystem::ApplySeason()
{
    switch (dayOfYear/90)
    {
        case 0: // winter
            for(list<Carnivore*>::iterator it=carnivoreList.begin(); it != carnivoreList.end(); it++) {
                if((*it)->getToken() == 'B') {
                    (*it)->setInHibernation(true);
                }
            }
            for(list<Herbivore*>::iterator it=herbivoreList.begin(); it != herbivoreList.end(); it++) {
                if((*it)->getToken() == 'G') {
                    (*it)->setInHibernation(true);
                }
            }
            growthPeriodPlants = 0; growthPeriodPlants = 10;
            growthPeriodAnimals = 30;
            breedingRepPeriodHerbivore =18; breedingRepPeriodCarnivore = 10;
            break;
        case 1: //spring
            growthPeriodPlants = 5; breedingRepPeriodPlants =10;
            growthPeriodAnimals = 20;
            breedingRepPeriodHerbivore =12; breedingRepPeriodCarnivore = 11;
            break;
        case 2: // summer
            growthPeriodPlants = 10; breedingRepPeriodPlants =10;
            growthPeriodAnimals = 30;
            breedingRepPeriodHerbivore =8; breedingRepPeriodCarnivore = 9;
            break;
        default: //autumn
            growthPeriodPlants = 0; breedingRepPeriodPlants =20;
            growthPeriodAnimals = 15;
            breedingRepPeriodHerbivore =5; breedingRepPeriodCarnivore = 9;
            break;
    }    
}

void ecosystem::DailyReset()
{
    for(list<Carnivore*>::iterator it=carnivoreList.begin(); it != carnivoreList.end(); it++) {
        (*it)->setIsHungry(true);
        if(dayOfYear%breedingRepPeriodCarnivore) {
            (*it)->setInHeat(true);
        }
        else {
            (*it)->setInHeat(false);
        }
    }
    for(list<Herbivore*>::iterator it=herbivoreList.begin(); it != herbivoreList.end(); it++) {
        (*it)->setIsHungry(true);
        if(dayOfYear%breedingRepPeriodHerbivore) {
            (*it)->setInHeat(true);
        }
        else {
            (*it)->setInHeat(false);
        }
    }
}

void ecosystem::AnimalMovement()
{
    for(list<Carnivore*>::iterator it=carnivoreList.begin(); it != carnivoreList.end(); it++) {
        if((*it)->getIsAlive()) {
            (*it)->Move(terrainSize);
        }
    }
    for(list<Herbivore*>::iterator it=herbivoreList.begin(); it != herbivoreList.end(); it++) {
        if((*it)->getIsAlive()) {
            (*it)->Move(terrainSize, terrain);
        }
    }
}

void ecosystem::CheckHunger()
{
    for(list<Carnivore*>::iterator it=carnivoreList.begin(); it != carnivoreList.end(); it++) {
        if((*it)->getIsHungry()) {
            (*it)->setHungerCount((*it)->getHungerCount() + 1);
            if((*it)->getHungerCount() == 10) {
                (*it)->Kill();
            }
        }
    }
    for(list<Herbivore*>::iterator it=herbivoreList.begin(); it != herbivoreList.end(); it++) {
        if((*it)->getIsHungry()) {
            (*it)->setHungerCount((*it)->getHungerCount() + 1);
            if((*it)->getHungerCount() == 10) {
                (*it)->Kill();
            }
        }
    }
}

void ecosystem::CheckDeadEntities()
{
    int hey = 0;
    for(list<Carnivore*>::iterator it=carnivoreList.begin(); it != carnivoreList.end(); ) {
        if(!(*it)->getIsAlive()) {
            // cout << hey++ << endl;
            it = carnivoreList.erase(it);
            // cout << hey++ << endl;
        }
        else it++;
    }
    for(list<Herbivore*>::iterator it=herbivoreList.begin(); it != herbivoreList.end(); ) {
        if(!(*it)->getIsAlive()) {
            it = herbivoreList.erase(it);
        }
        else it++;
    }
    for(list<Seeded*>::iterator it=seededList.begin(); it != seededList.end(); ) {
        if((*it)->getLife() == 0) {
            it = seededList.erase(it);
        }
        else it++;
    }
    for(list<Seedless*>::iterator it=seedlessList.begin(); it != seedlessList.end(); ) {
        if((*it)->getLife() ==  0) {
            it = seedlessList.erase(it);
        }
        else it++;
    }
}

char ecosystem::findAnimal(const int& x, const int& y)
{
    std::list<Herbivore*>::iterator itH;
    std::list<Carnivore*>::iterator itC;

    for(itH = herbivoreList.begin(); itH!=herbivoreList.end(); itH++) {
        if((*itH)->getPointX()==x && (*itH)->getPointY()==y) {
            return (*itH)->getToken();
        }
    }
    for(itC = carnivoreList.begin(); itC!=carnivoreList.end(); itC++) {
        if((*itC)->getPointX()==x && (*itC)->getPointY()==y) {
            return (*itC)->getToken();
        }
    }

    return '0';
}

void ecosystem::PrintSystem()
{   
    std::cout << std::endl;
    for(int i=0; i < terrainSize; i++) {
        for(int j=0; j < terrainSize; j++) {
            std::cout << terrain[j][i]->getEnvironment() << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void ecosystem::PrintAnimals()
{
    char myToken;

    for(int i=0; i < terrainSize; i++) {
        for(int j=0; j < terrainSize; j++) {
            myToken = findAnimal(j, i);
            if(myToken != '0') {
                std::cout << myToken << " ";
            }
            else {
                std::cout << terrain[j][i]->getEnvironment() << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}