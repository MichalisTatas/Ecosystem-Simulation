#include <iostream>
#include <cstdlib>
#include "../include/classes.h"

using namespace std;

ecosystem:: ecosystem(const int& terainSize, const int& dayOfYear)
    :terrainSize(terrainSize), dayOfYear(dayOfYear)
{
    MapGenerator();
    GenerateRiver();
    GenerateLake();
    GenerateHills();
    GenerateMeadow();
}

ecosystem:: ~ecosystem()
{
    for(int i=0; i < terrainSize; i++) {
        for(int j=0; j < terrainSize; j++) {
            delete[] terrain[i][j];
        }
        delete[] terrain[i];
    }
    delete[] terrain;
}

void ecosystem:: MapGenerator()
{    
    terrain = new tiles**[terrainSize];
    for(int i=0; i < terrainSize; i++) {
        terrain[i] = new tiles*[terrainSize];
        for(int j=0; j < terrainSize; j++) {
            terrain[i][j] = new tiles();
        }
    }
}

void ecosystem:: GenerateRiver()
{
    int x=rand()%5, y=rand()%(terrainSize-5);
    terrain[x][y]->changeEnviroment('#');

    if(rand()%10 < 3) {
        for(int i=0; i < terrainSize-x-1; i++) {
            switch (rand()%4)
            {
                case 0:
                    terrain[x][++y]->changeEnviroment('#');
                    terrain[++x][y]->changeEnviroment('#');
                    break;
                case 1:
                    terrain[x][++y]->changeEnviroment('#');
                    terrain[x][++y]->changeEnviroment('#');
                    terrain[++x][y]->changeEnviroment('#');
                    break;
                case 2:
                    terrain[x][--y]->changeEnviroment('#');
                    terrain[x++][y]->changeEnviroment('#');
                    break;
                case 3:
                    terrain[x][--y]->changeEnviroment('#');
                    terrain[x][--y]->changeEnviroment('#');
                    terrain[++x][y]->changeEnviroment('#');
                    break;
            }
        }
    }
    else {
        terrain[++x][y]->changeEnviroment('#');
    }
}

void ecosystem:: GenerateLake()
{

}

void ecosystem:: GenerateHills()
{
    
}

void ecosystem:: GenerateMeadow()
{
    
}