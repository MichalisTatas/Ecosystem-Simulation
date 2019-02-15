#include <iostream>
#include <cstdlib>
#include "../include/classes.h"

using namespace std;

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
    cout << "Generating terrain..." << endl;
    MapGenerator();
    GenerateRiver();
    GenerateLake();
    GenerateHills();
    GenerateMeadow();
    cout << "Terrain Generated!" << endl;
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
    cout << "Map Generated" << endl;
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
    cout << "River Generated" << endl;
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
    cout << "Lake Generated" << endl;
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
    cout << "Hills Generated" << endl;
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
    cout << "Meadow Generated" << endl;
}

void ecosystem:: PrintSystem() {
    for(int i=0; i < terrainSize; i++) {
        for(int j=0; j < terrainSize; j++) {
            cout << terrain[j][i]->getEnviroment() << " ";
        }
        cout << endl;
    }
    cout << endl;
}