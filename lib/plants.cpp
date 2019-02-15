#include <iostream>
#include "../include/plants.h"
#include "../include/classes.h"
#include <string>

/////////////////////
//Plant's functions//
/////////////////////
Plant::Plant(){}
Plant::Plant(char mytoken,string myname,int mylife,int myillnessProb,int mybreedingProb,int mylifeFactor)
    : token(mytoken), name(myname), life(mylife), illnessProb(myillnessProb), breedingProb(mybreedingProb),lifeFactor(mylifeFactor)
{}
Plant::~Plant(){}

int Plant::get_breedingProb(){
    return breedingProb;
}

int Plant::get_illnessProb(){
    return illnessProb;
}

int Plant::get_life(){
    return life;
}

int Plant::get_lifeFactor(){
    return lifeFactor;
}

void Plant::LoseLife(){
    life = life - lifeFactor;
}

//////////////////////////
//SeededPlant's fuctions//
//////////////////////////
SeededPlant:: SeededPlant(char mytoken)
{
    switch(mytoken){
        case 'M' :    
                    seeds = 10;
                    foliage = 20;
                    size = 2;
                    Plant(mytoken,"Maple",20,5,5,10);
        break;
        case 'O' : 
                    seeds = 15;
                    foliage = 30;
                    size = 5;
                    Plant(mytoken,"Oak",30,20,20,15);
        break;
        case 'P' :
                    seeds = 20;;
                    foliage = 40;
                    size = 5;
                    Plant(mytoken,"Pine",40,15,15,20);
        break;
    }
}

SeededPlant:: ~SeededPlant(){}

int SeededPlant::get_foliage(){
    return foliage;
}

int SeededPlant::get_seeds(){
    return seeds;
}

void SeededPlant::LoseSeeds(){
    seeds = seeds - lifeFactor;
}

void SeededPlant::LoseFoliage(){
    foliage = foliage - lifeFactor;
    life = life - lifeFactor; //is it right? do i need both?
}

//////////////////////////////
//SeedlessPlant's functions//
//////////////////////////////

SeedlessPlant::SeedlessPlant(char mytoken){
    switch(mytoken){
        case 'G' :
                    Plant(mytoken,"Grass",5,15,15,4);
        break;
        case 'A':
                    Plant(mytoken,"Algae",5,25,25,2);
        break;
    }
}

SeedlessPlant::~SeedlessPlant(){}

