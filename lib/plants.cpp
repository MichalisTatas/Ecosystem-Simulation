#include <iostream>
#include "../include/plants.h"
#include "../include/classes.h"
#include <string>

/////////////////////
//Plant's functions//
/////////////////////
Plant::Plant()
{

}

Plant::Plant(char myToken, string myName, const int& myLife, const int& myIllnessProb, const int& myBreedingProb, const int& myLifeFactor)
    : token(myToken), name(myName), life(myLife), illnessProb(myIllnessProb), breedingProb(myBreedingProb),lifeFactor(myLifeFactor)
{

}
Plant::~Plant()
{

}

int Plant::getBreedingProb()
{
    return breedingProb;
}

int Plant::getIllnessProb()
{
    return illnessProb;
}

int Plant::getLife()
{
    return life;
}

int Plant::getLifeFactor()
{
    return lifeFactor;
}

void Plant::LoseLife()
{
    life = life - lifeFactor;
}

//////////////////////////
//Seeded's fuctions//
//////////////////////////
Seeded:: Seeded(char myToken)
{
    switch(myToken){
        case 'M' :    
            seeds = 10;
            foliage = 20;
            size = 2;
            Plant(myToken,"Maple",20,5,5,10);
            break;
        case 'O' : 
            seeds = 15;
            foliage = 30;
            size = 5;
            Plant(myToken,"Oak",30,20,20,15);
            break;
        case 'P' :
                seeds = 20;;
                foliage = 40;
                size = 5;
                Plant(myToken,"Pine",40,15,15,20);
            break;
    }
}

Seeded:: ~Seeded()
{

}

int Seeded::getFoliage()
{
    return foliage;
}

int Seeded::getSeeds()
{
    return seeds;
}

void Seeded::LoseSeeds()
{
    seeds = seeds - lifeFactor;
}

void Seeded::LoseFoliage()
{
    foliage = foliage - lifeFactor;
    life = life - lifeFactor; //is it right? do i need both?
}

//////////////////////////////
//Seedless's functions//
//////////////////////////////

Seedless::Seedless(char myToken)
{
    switch(myToken){
        case 'G' :
            Plant(myToken,"Grass",5,15,15,4);
            break;
        case 'A':
            Plant(myToken,"Algae",5,25,25,2);
            break;
    }
}

Seedless::~Seedless()
{

}