#include <iostream>
#include <cstdlib>
#include <list>
#include "../include/classes.h"

// using namespace std;

tiles::tiles()
    : enviroment('0')
{

}

char tiles::getEnviroment()
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
                if(terrain[x][y++]->getEnviroment() != '0') {
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
            if(terrain[i][j]->getEnviroment()!='#' && terrain[i][j]->getEnviroment()!='^') {
                terrain[i][j]->setEnviroment('"');
            }
        }
    }
    std::cout << "Meadow Generated" << std::endl;
}

void ecosystem::PlacePlants()
{
    for(int x=0; x < terrainSize; x++) {
        for(int y=0; y < terrainSize; y++) {
            if(rand()%10 < 3) {
                switch (terrain[x][y]->getEnviroment()) {
                    case '"':
                        switch (rand()%3) {
                            case 1: {
                                Seeded myPlant('M', x, y);
                                terrain[x][y]->setEnviroment('M');
                                seededList.push_front(myPlant);
                                break;
                            }
                            case 2: {
                                Seeded myPlant('O', x, y);
                                terrain[x][y]->setEnviroment('O');
                                seededList.push_front(myPlant);
                                break;
                            }
                            default:
                                Seedless myPlant('G', x, y);
                                terrain[x][y]->setEnviroment('G');
                                seedlessList.push_front(myPlant);
                                break;
                        }
                        break;
                    case '^':
                        switch (rand()%2) {
                            case 1: {
                                Seeded myPlant('M', x, y);
                                terrain[x][y]->setEnviroment('M');
                                seededList.push_front(myPlant);
                                break;
                            }
                            default:
                                Seeded myPlant('P', x, y);
                                terrain[x][y]->setEnviroment('P');
                                seededList.push_front(myPlant);
                                break;
                        }
                        break;
                    default:
                        Seedless myPlant('A', x, y);
                        terrain[x][y]->setEnviroment('A');
                        seedlessList.push_front(myPlant);
                        break;
                }
            }
        }
    }
}

void ecosystem::PlaceAnimals()
{
    for(int x=0; x < terrainSize; x++) {
        for(int y=0; y < terrainSize; y++) {
            if(rand()%10 < 4) {
                switch (terrain[x][y]->getEnviroment()) {
                    case '"':
                        switch (rand()%5) {
                            case 1: {
                                Herbivore myAnimal('D', x, y);
                                herbivoreList.push_front(myAnimal);
                                break;
                            }
                            case 2: {
                                Herbivore myAnimal('R', x, y);
                                herbivoreList.push_front(myAnimal);
                                break;
                            }
                            case 3: {
                                Herbivore myAnimal('G', x, y);
                                herbivoreList.push_front(myAnimal);
                                break;
                            }
                            case 4: {
                                Carnivore myAnimal('F', x, y);
                                carnivoreList.push_front(myAnimal);
                                break;
                            }
                            default:
                                Carnivore myAnimal('W', x, y);
                                carnivoreList.push_front(myAnimal);
                                break;
                        }
                        break;
                    case '^':
                        switch (rand()%2) {
                            case 0: {
                                Carnivore myAnimal('W', x, y);
                                carnivoreList.push_front(myAnimal);
                                break;
                            }
                            default:
                                Carnivore myAnimal('B', x, y);
                                carnivoreList.push_front(myAnimal);
                                break;
                        }
                        break;
                    default:
                        Herbivore myAnimal('S', x, y);
                        herbivoreList.push_front(myAnimal);
                        break;
                }
            }
        }
    }
}

void ecosystem::PrintSystem() {
    for(int i=0; i < terrainSize; i++) {
        for(int j=0; j < terrainSize; j++) {
            std::cout << terrain[j][i]->getEnviroment() << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}