#include <iostream>
#include <cstdlib>
#include <list>
#include <iterator>
#include "../include/classes.h"

// using namespace std;

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
                                seededList.push_front(seededPlant);
                                break;
                            }
                            case 2: {
                                seededPlant = new Seeded('O', x, y);
                                seededList.push_front(seededPlant);
                                break;
                            }
                            default:
                                seedlessPlant = new Seedless('G', x, y);
                                seedlessList.push_front(seedlessPlant);
                                break;
                        }
                        break;
                    case '^':
                        switch (rand()%2) {
                            case 1: {
                                seededPlant = new Seeded('M', x, y);
                                seededList.push_front(seededPlant);
                                break;
                            }
                            default:
                                seededPlant = new Seeded('P', x, y);
                                seededList.push_front(seededPlant);
                                break;
                        }
                        break;
                    default:
                        seedlessPlant = new Seedless('A', x, y);
                        seedlessList.push_front(seedlessPlant);
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
                                herbivoreList.push_front(herbivoreAnimal);
                                break;
                            }
                            case 1: {
                                herbivoreAnimal = new Herbivore('R', x, y);
                                herbivoreList.push_front(herbivoreAnimal);
                                break;
                            }
                            case 2: {
                                herbivoreAnimal = new Herbivore('G', x, y);
                                herbivoreList.push_front(herbivoreAnimal);
                                break;
                            }
                            case 3: {
                                carnivoreAnimal = new Carnivore('F', x, y);
                                carnivoreList.push_front(carnivoreAnimal);
                                break;
                            }
                            default:
                                carnivoreAnimal = new Carnivore('W', x, y);
                                carnivoreList.push_front(carnivoreAnimal);
                                break;
                        }
                        break;
                    case '^':
                        switch (rand()%2) {
                            case 0: {
                                carnivoreAnimal = new Carnivore('W', x, y);
                                carnivoreList.push_front(carnivoreAnimal);
                                break;
                            }
                            default:
                                carnivoreAnimal = new Carnivore('B', x, y);
                                carnivoreList.push_front(carnivoreAnimal);
                                break;
                        }
                        break;
                    default:
                        herbivoreAnimal = new Herbivore('S', x, y);
                        herbivoreList.push_front(herbivoreAnimal);
                        break;
                }
            }
        }
    }
}
void ecosystem::RunEcosystem(const int& numberOdDays)
{
    for(int i=0; i < numberOdDays; i++) {
        // ApplySeason();
        // DailyReset();
        // AnimalMovement();
        // AnimalEating();
        // CheckDeadEntities();
        // CheckHunger();
        // AnimalBreeding();
        // PlantBreeding();
    }
}

void ecosystem::ApplySeason()
{
    
}

/*void ecosystem::RunEcosystem(){
    for(int i=0; i<dayOfYear; i++){
        switch(i/90){
            case 1 :                                    //Spring
            break;
            case 2 :                                    //Summer
            break;
            case 3 :                                    //Autumn
            break;
            case 4 :                                    //Winter
            break;
        }
    }
}
*/

char ecosystem::findAnimal(const int& x, const int& y)
{
    std::list<Herbivore*>::iterator itH;
    std::list<Carnivore*>::iterator itC;

    for(itH = herbivoreList.begin(); itH!=herbivoreList.end(); itH++) {
        if((*itH)->getPointX()==x && (*itH)->getPointY()==y) {
            return '7';
            // return itH->getToken();
        }
    }
    for(itC = carnivoreList.begin(); itC!=carnivoreList.end(); itC++) {
        if((*itC)->getPointX()==x && (*itC)->getPointY()==y) {
            return '7';
            // return itC->getToken();
        }
    }

    return '0';
}

void ecosystem::PrintSystem() {
    for(int i=0; i < terrainSize; i++) {
        for(int j=0; j < terrainSize; j++) {
            std::cout << terrain[j][i]->getEnvironment() << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    PrintAnimals();

    std::list<Herbivore*>::iterator itH;

    for(itH = herbivoreList.begin(); itH!=herbivoreList.end(); itH++) {
        std::cout << (*itH)->getPointX() << " " << (*itH)->getPointY() << std::endl; 
    }
    
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