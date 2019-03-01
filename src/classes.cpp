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

bool tiles::getHasPlant()
{
    return hasPlant;
}

void tiles::setHasPLant(bool a)
{
    hasPlant = a;    
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
    std::cout << "Terrain Generated!" << std::endl;
    PrintMap();
    cout << "Generating Life..." << endl;
    PlacePlants(); PrintPlants(); 
    PlaceAnimals(); PrintAnimals();
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

    for(list<Carnivore*>::iterator it=carnivoreList.begin(); it != carnivoreList.end(); ) {
        delete *it;
        it = carnivoreList.erase(it);
    }
    for(list<Herbivore*>::iterator it=herbivoreList.begin(); it != herbivoreList.end(); ) {
        delete *it;
        it = herbivoreList.erase(it);
    }
    for(list<Seeded*>::iterator it=seededList.begin(); it != seededList.end(); ) {
        delete *it;
        it = seededList.erase(it);
    }
    for(list<Seedless*>::iterator it=seedlessList.begin(); it != seedlessList.end(); ) {
        delete *it;
        it = seedlessList.erase(it);
    }
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
    int x=0, y= 4 + rand()%(terrainSize-8);
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
    int size, hills=terrainSize/5, x, y, joker;
    bool cleanGround = true;

    for(int count=0; count < hills; ) {
        size = (rand()%3)+2;
        x = rand()%(terrainSize-size);
        y = rand()%(terrainSize-size);
        joker = y;
        cleanGround = true;

        for(int i=0; i < size; i++) {
            for(int j=0; j < size; j++) {
                if(terrain[x][y++]->getEnvironment() != '0') {
                    cleanGround = false;
                }
            }
            y = joker; x++;
        }
        if(cleanGround) {
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
    int count = 0;

    for(int x=0; x < terrainSize; x++) {
        for(int y=0; y < terrainSize; y++) {
            if(rand()%10 < 3) {
                switch (terrain[x][y]->getEnvironment()) {
                    case '"':
                        switch (rand()%3) {
                            case 1: {
                                seededPlant = new Seeded('M', x, y);
                                terrain[x][y]->setHasPLant(true);
                                seededList.push_back(seededPlant);
                                // delete seededPlant;
                                count ++;
                                break;
                            }
                            case 2: {
                                seededPlant = new Seeded('O', x, y);
                                terrain[x][y]->setHasPLant(true);
                                seededList.push_back(seededPlant);
                                // delete seededPlant;
                                count ++;
                                break;
                            }
                            default:
                                seedlessPlant = new Seedless('G', x, y);
                                terrain[x][y]->setHasPLant(true);
                                seedlessList.push_back(seedlessPlant);
                                // delete seedlessPlant;
                                count ++;
                                break;
                        }
                        break;
                    case '^':
                        switch (rand()%2) {
                            case 1: {
                                seededPlant = new Seeded('M', x, y);
                                terrain[x][y]->setHasPLant(true);
                                seededList.push_back(seededPlant);
                                // delete seededPlant;
                                count ++;
                                break;
                            }
                            default:
                                seededPlant = new Seeded('P', x, y);
                                terrain[x][y]->setHasPLant(true);
                                seededList.push_back(seededPlant);
                                // delete seededPlant;
                                count ++;
                                break;
                        }
                        break;
                    default:
                        seedlessPlant = new Seedless('A', x, y);
                        terrain[x][y]->setHasPLant(true);
                        seedlessList.push_back(seedlessPlant);
                        // delete seedlessPlant;
                        count ++;
                        break;
                }
            }
        }
    }
    cout << endl << "Plants Generated: " << count << endl;
}

void ecosystem::PlaceAnimals()
{
    Herbivore* herbivoreAnimal;
    Carnivore* carnivoreAnimal;
    int count = 0;

    for(int x=0; x < terrainSize; x++) {
        for(int y=0; y < terrainSize; y++) {
            if(rand()%10 < 4) {
                switch (terrain[x][y]->getEnvironment()) {
                    case '"':
                        switch (rand()%5) {
                            case 0: {
                                herbivoreAnimal = new Herbivore('D', x, y);
                                herbivoreAnimal->eloBoost();
                                herbivoreList.push_back(herbivoreAnimal);
                                // delete herbivoreAnimal;
                                count++;
                                break;
                            }
                            case 1: {
                                herbivoreAnimal = new Herbivore('R', x, y);
                                herbivoreAnimal->eloBoost();
                                herbivoreList.push_back(herbivoreAnimal);
                                // delete herbivoreAnimal;
                                count++;
                                break;
                            }
                            case 2: {
                                herbivoreAnimal = new Herbivore('G', x, y);
                                herbivoreAnimal->eloBoost();
                                herbivoreList.push_back(herbivoreAnimal);
                                // delete herbivoreAnimal;
                                count++;
                                break;
                            }
                            case 3: {
                                carnivoreAnimal = new Carnivore('F', x, y);
                                carnivoreAnimal->eloBoost();
                                carnivoreList.push_back(carnivoreAnimal);
                                // delete carnivoreAnimal;
                                count++;
                                break;
                            }
                            default:
                                carnivoreAnimal = new Carnivore('W', x, y);
                                carnivoreAnimal->eloBoost();
                                carnivoreList.push_back(carnivoreAnimal);
                                // delete carnivoreAnimal;
                                count++;
                                break;
                        }
                        break;
                    case '^':
                        switch (rand()%8) {
                            case 0: {
                                carnivoreAnimal = new Carnivore('W', x, y);
                                carnivoreAnimal->eloBoost();
                                carnivoreList.push_back(carnivoreAnimal);
                                // delete carnivoreAnimal;
                                count++;
                                break;
                            }
                            case 1:
                                carnivoreAnimal = new Carnivore('B', x, y);
                                carnivoreAnimal->eloBoost();
                                carnivoreList.push_back(carnivoreAnimal);
                                // delete carnivoreAnimal;
                                count++;
                                break;
                        }
                        break;
                    default:
                        herbivoreAnimal = new Herbivore('S', x, y);
                        herbivoreAnimal->eloBoost();
                        herbivoreList.push_back(herbivoreAnimal);
                        // delete herbivoreAnimal;
                        count++;
                        break;
                }
            }
        }
    }
    cout << "Animals Generated:" << count << endl;
}
void ecosystem::RunEcosystem(const int& numberOdDays)
{
    for(int i=0; i < numberOdDays; i++) {
        dayOfYear++;
        if(dayOfYear == 361) {
            dayOfYear = 1;
            cout << "3" << endl << "2" << endl << "1" << endl << "Happy New Year!!!" << endl;
        }
        switch (dayOfYear) {
            case 1:
                ApplySeason(0);
                PrintSystem();
                break;
            case 91:
                ApplySeason(1);
                PrintSystem();
                break;
            case 181:
                ApplySeason(2);
                PrintSystem();
                break;
            case 271:
                ApplySeason(3);
                PrintSystem();
                break;
        }
        DailyReset();
        // PrintAnimals();
        for(int j=0; j < 24; j++) {
            AnimalMovement();
            AnimalEating();
        }
        CheckHunger();
        CheckDeadEntities();
        AnimalBreeding();
        PlantBreeding();
        cout << endl;
    }
}

void ecosystem::ApplySeason(const int& day)
{
    switch (day) {
        case 0: // winter
            for(list<Carnivore*>::iterator it=carnivoreList.begin(); it != carnivoreList.end(); it++) {
                if((*it)->getHibernates()) {
                    (*it)->setInHibernation(true);
                }
            }
            for(list<Herbivore*>::iterator it=herbivoreList.begin(); it != herbivoreList.end(); it++) {
                if((*it)->getHibernates()) {
                    (*it)->setInHibernation(true);
                }
            }
            growthPeriodPlants = 0; breedingRepPeriodPlants = 10;
            growthPeriodAnimals = 30;
            breedingRepPeriodHerbivore =18; breedingRepPeriodCarnivore = 10;
            cout << "Current season: Winter" << endl;
            break;
        case 1: //spring
            for(list<Carnivore*>::iterator it=carnivoreList.begin(); it != carnivoreList.end(); it++) {
                if((*it)->getToken() == 'B') {
                    (*it)->setInHibernation(false);
                }
            }
            for(list<Herbivore*>::iterator it=herbivoreList.begin(); it != herbivoreList.end(); it++) {
                if((*it)->getToken() == 'G') {
                    (*it)->setInHibernation(false);
                }
            }
            growthPeriodPlants = 5; breedingRepPeriodPlants =10;
            growthPeriodAnimals = 20;
            breedingRepPeriodHerbivore =12; breedingRepPeriodCarnivore = 11;
            cout << "Current season: Spring" << endl;
            break;
        case 2: // summer
            growthPeriodPlants = 10; breedingRepPeriodPlants =10;
            growthPeriodAnimals = 30;
            breedingRepPeriodHerbivore =8; breedingRepPeriodCarnivore = 9;
            cout << "Current season: Summer" << endl;
            break;
        default: //autumn
            growthPeriodPlants = 0; breedingRepPeriodPlants =20;
            growthPeriodAnimals = 15;
            breedingRepPeriodHerbivore =5; breedingRepPeriodCarnivore = 9;
            cout << "Current season: Autumn" << endl;
            break;
    }    
}

void ecosystem::DailyReset()
{
    for(list<Carnivore*>::iterator it=carnivoreList.begin(); it != carnivoreList.end(); it++) {
        if(!(*it)->getInHibernation()) {
            (*it)->setIsHungry(true);
            if(dayOfYear%breedingRepPeriodCarnivore == 0) {
                (*it)->setInHeat(true); 

            }
            else {
                (*it)->setInHeat(false);
            }
            if(dayOfYear%growthPeriodAnimals == 0) {
                (*it)->Raise();
            }
        }
    }
    for(list<Herbivore*>::iterator it=herbivoreList.begin(); it != herbivoreList.end(); it++) {
        if(!(*it)->getInHibernation()) {
            if((*it)->getHungerCount()==7) {
                if(!(*it)->getIsHungry()) {
                    (*it)->setIsHungry(true);
                    (*it)->setHungerCount(0);
                }
            }
            if(dayOfYear%breedingRepPeriodHerbivore == 0) {
                (*it)->setInHeat(true);
            }
            else {
                    (*it)->setInHeat(false);
            }
            if(dayOfYear%growthPeriodAnimals == 0) {
                (*it)->Raise();
            }
        }
    }
    for(list<Seeded*>::iterator it=seededList.begin(); it != seededList.end(); it++) {
        if(dayOfYear&growthPeriodPlants == 0) {
            if(rand()%100 < (*it)->getIllnessProb())
                (*it)->Growth(false);
            else
                (*it)->Growth(true);
        }
    }
    for(list<Seedless*>::iterator it=seedlessList.begin(); it != seedlessList.end(); it++) {
        if(dayOfYear&growthPeriodPlants == 0) {
            if(rand()%100 < (*it)->getIllnessProb()) {
                (*it)->LoseLife((*it)->getLifeFactor());
            }
            else {
                (*it)->Growth();
            }
        }
    }
}

void ecosystem::AnimalMovement()
{
    for(list<Carnivore*>::iterator it=carnivoreList.begin(); it != carnivoreList.end(); it++) {
        if((*it)->getIsAlive() && !(*it)->getInHibernation()) {
            (*it)->Move(terrainSize);
        }
    }
    for(list<Herbivore*>::iterator it=herbivoreList.begin(); it != herbivoreList.end(); it++) {
        if((*it)->getIsAlive() && !(*it)->getInHibernation()) {
            (*it)->Move(terrainSize, terrain);
        }
    }
}

void ecosystem::AnimalEating()
{
    for(list<Carnivore*>::iterator it=carnivoreList.begin(); it != carnivoreList.end(); it++) {
        if(!(*it)->getInHibernation()) {
            if((*it)->getIsHungry()) {
                if(findHerbivore((*it)->getPointX(), (*it)->getPointY(), (*it)->getSize(), (*it)->getSpeed())) {
                    (*it)->setIsHungry(false);
                    (*it)->setHungerCount(0);
                }
            }
        }
    }
    for(list<Herbivore*>::iterator it=herbivoreList.begin(); it != herbivoreList.end(); it++) {
        if(!(*it)->getInHibernation()) {
            if((*it)->getIsHungry()) {
                (*it)->setEatenFood(findPLantToEat((*it)->getPointX(), (*it)->getPointY(), (*it)->getToken(), (*it)->getSize(), (*it)->getEatMax(), (*it)->getCanClimb()));
                if((*it)->getEatenFood() == (*it)->getNeededFood()) {
                    (*it)->setIsHungry(false);
                    (*it)->setEatenFood(0);
                    (*it)->setHungerCount(0);
                }
            }
        }
    }
}

void ecosystem::CheckHunger()
{
    for(list<Carnivore*>::iterator it=carnivoreList.begin(); it != carnivoreList.end(); it++) {
        if(!(*it)->getInHibernation())
            if((*it)->getIsHungry()) {
                (*it)->setHungerCount((*it)->getHungerCount() + 1);
                if((*it)->getHungerCount() == 10) {
                    (*it)->Kill();
                }
            }
    }
    for(list<Herbivore*>::iterator it=herbivoreList.begin(); it != herbivoreList.end(); it++) {
        if(!(*it)->getInHibernation())
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
        int animCount = 0, plaCount = 0;

    for(list<Carnivore*>::iterator it=carnivoreList.begin(); it != carnivoreList.end(); ) {
        if(!(*it)->getIsAlive()) {
            
            delete *it;
            it = carnivoreList.erase(it);
            animCount++;
        }
        else it++;
    }
    for(list<Herbivore*>::iterator it=herbivoreList.begin(); it != herbivoreList.end(); ) {
        if(!(*it)->getIsAlive()) {
            delete *it;
            it = herbivoreList.erase(it);
            animCount++;
        }
        else it++;
    }
    for(list<Seeded*>::iterator it=seededList.begin(); it != seededList.end(); ) {
        if((*it)->getLife() == 0) {
            terrain[(*it)->getPointX()][(*it)->getPointY()]->setHasPLant(false);
            delete *it;
            it = seededList.erase(it);
            plaCount++;
        }
        else it++;
    }
    for(list<Seedless*>::iterator it=seedlessList.begin(); it != seedlessList.end(); ) {
        if((*it)->getLife() ==  0) {
            terrain[(*it)->getPointX()][(*it)->getPointY()]->setHasPLant(false);
            delete *it;
            it = seedlessList.erase(it);
            plaCount++;
        }
        else it++;
    }
    cout << animCount << " animals died this day!" << endl;
    cout << plaCount << " plants died this day!" << endl;
}

void ecosystem::AnimalBreeding()
{
    Carnivore* myCarnivore;
    Herbivore* myHerbivore;
    int carnCount = 0, herbCount = 0;

    for(list<Carnivore*>::iterator it=carnivoreList.begin(); it != carnivoreList.end(); it++) {
        if((*it)->getInHeat()) {
            if(rand()%10 < 5) {
                myCarnivore = new Carnivore((*it)->getToken(), (*it)->getPointX(), (*it)->getPointY());
                carnivoreList.push_front(myCarnivore);
                carnCount++;
            }
        }
    }
    for(list<Herbivore*>::iterator it=herbivoreList.begin(); it != herbivoreList.end(); it++) {
        if((*it)->getInHeat()) {
            if(true) {
                myHerbivore = new Herbivore((*it)->getToken(), (*it)->getPointX(), (*it)->getPointY());
                herbivoreList.push_front(myHerbivore);
                herbCount++;
            }
        }
    }
    cout << carnCount << " new baby Carnivore Animals!" << endl;
    cout << herbCount << " new baby Herbivore Animals!" << endl;
}

void ecosystem::PlantBreeding()
{
    Seeded* mySeeded;
    Seedless* mySeedless;
    point location;
    int edCount = 0, lessCount = 0;

    if(dayOfYear%breedingRepPeriodPlants == 0) {
        for(list<Seeded*>::iterator it=seededList.begin(); it != seededList.end(); it++) {
            if(rand()%100 < (*it)->getBreedingProb()) {
                location = FindFreeTile((*it)->getToken(), (*it)->getPointX(), (*it)->getPointY());
                if(location.x != -1 && location.y != -1) {
                    mySeeded = new Seeded((*it)->getToken(), location.x, location.y);
                    seededList.push_front(mySeeded);
                    edCount++;
                }
            }
        }
        for(list<Seedless*>::iterator it=seedlessList.begin(); it != seedlessList.end(); it++) {
            if(rand()%100 < (*it)->getBreedingProb()) {
                location = FindFreeTile((*it)->getToken(), (*it)->getPointX(), (*it)->getPointY());
                if(location.x != -1 && location.y != -1) {
                    mySeedless = new Seedless((*it)->getToken(), location.x, location.y);
                    seedlessList.push_front(mySeedless);
                    lessCount++;
                }
            }
        }
    }
    cout << edCount << " new Seeded Plants" << endl;
    cout << lessCount << " new Seedless Plants" << endl;
}

point ecosystem::FindFreeTile(char token, const int& x, const int& y)
{
    point location;

    switch (token) {
        case 'P': //mountains only
            if(x > 0) {
                if(!terrain[x-1][y]->getHasPlant() && terrain[x-1][y]->getEnvironment() == '^') {
                    location.x = x-1; location.y = y;
                    return location;
                }
            }
            if(x < terrainSize-1) {
                if(!terrain[x+1][y]->getHasPlant() && terrain[x+1][y]->getEnvironment() == '^') {
                    location.x = x+1; location.y = y;
                    return location;
                }
            }
            if(y > 0) {
                if(!terrain[x][y-1]->getHasPlant() && terrain[x][y-1]->getEnvironment() == '^') {
                    location.x = x; location.y = y-1;
                    return location;
                }
            }
            if(y < terrainSize-1) {
                if(!terrain[x][y+1]->getHasPlant() && terrain[x][y+1]->getEnvironment() == '^') {
                    location.x = x; location.y = y+1;
                    return location;
                }
            }
            break;
        case 'M': //land
            if(x > 0) {
                if(!terrain[x-1][y]->getHasPlant() && terrain[x-1][y]->getEnvironment() != '#') {
                    location.x = x-1; location.y = y;
                    return location;
                }
            }
            if(x < terrainSize-1) {
                if(!terrain[x+1][y]->getHasPlant() && terrain[x+1][y]->getEnvironment() != '#') {
                    location.x = x+1; location.y = y;
                    return location;
                }
            }
            if(y > 0) {
                if(!terrain[x][y-1]->getHasPlant() && terrain[x][y-1]->getEnvironment() != '#') {
                    location.x = x; location.y = y-1;
                    return location;
                }
            }
            if(y < terrainSize-1) {
                if(!terrain[x][y+1]->getHasPlant() && terrain[x][y+1]->getEnvironment() != '#') {
                    location.x = x; location.y = y+1;
                    return location;
                }
            }
            break;
        case 'G': //fields only
            if(x > 0) {
                if(!terrain[x-1][y]->getHasPlant() && terrain[x-1][y]->getEnvironment() == '"') {
                    location.x = x-1; location.y = y;
                    return location;
                }
            }
            if(x < terrainSize-1) {
                if(!terrain[x+1][y]->getHasPlant() && terrain[x+1][y]->getEnvironment() == '"') {
                    location.x = x+1; location.y = y;
                    return location;
                }
            }
            if(y > 0) {
                if(!terrain[x][y-1]->getHasPlant() && terrain[x][y-1]->getEnvironment() == '"') {
                    location.x = x; location.y = y-1;
                    return location;
                }
            }
            if(y < terrainSize-1) {
                if(!terrain[x][y+1]->getHasPlant() && terrain[x][y+1]->getEnvironment() == '"') {
                    location.x = x; location.y = y+1;
                    return location;
                }
            }
            break;
        case 'O': //fields only
            if(x > 0) {
                if(!terrain[x-1][y]->getHasPlant() && terrain[x-1][y]->getEnvironment() == '"') {
                    location.x = x-1; location.y = y;
                    return location;
                }
            }
            if(x < terrainSize-1) {
                if(!terrain[x+1][y]->getHasPlant() && terrain[x+1][y]->getEnvironment() == '"') {
                    location.x = x+1; location.y = y;
                    return location;
                }
            }
            if(y > 0) {
                if(!terrain[x][y-1]->getHasPlant() && terrain[x][y-1]->getEnvironment() == '"') {
                    location.x = x; location.y = y-1;
                    return location;
                }
            }
            if(y < terrainSize-1) {
                if(!terrain[x][y+1]->getHasPlant() && terrain[x][y+1]->getEnvironment() == '"') {
                    location.x = x; location.y = y+1;
                    return location;
                }
            }
            break;
        default: //water
            if(x > 0) {
                if(!terrain[x-1][y]->getHasPlant() && terrain[x-1][y]->getEnvironment() == '#') {
                    location.x = x-1; location.y = y;
                    return location;
                }
            }
            if(x < terrainSize-1) {
                if(!terrain[x+1][y]->getHasPlant() && terrain[x+1][y]->getEnvironment() == '#') {
                    location.x = x+1; location.y = y;
                    return location;
                }
            }
            if(y > 0) {
                if(!terrain[x][y-1]->getHasPlant() && terrain[x][y-1]->getEnvironment() == '#') {
                    location.x = x; location.y = y-1;
                    return location;
                }
            }
            if(y < terrainSize-1) {
                if(!terrain[x][y+1]->getHasPlant() && terrain[x][y+1]->getEnvironment() == '#') {
                    location.x = x; location.y = y+1;
                    return location;
                }
            }
            break;
    }
        location.x = -1; location.y = -1;
        return location;
}

bool ecosystem::findHerbivore(const int& x, const int& y, const int& size, const int& speed)
{   
    for(list<Herbivore*>::iterator it=herbivoreList.begin(); it != herbivoreList.end(); it++) {
        if((*it)->getPointX()==x && (*it)->getPointY() ==y) {
            if((*it)->getSize()<=size && (*it)->getSpeed()<=speed) {
                herbivoreList.erase(it);
                return true;
            }
        }
    }
    return false;
}

int ecosystem::findPLantToEat(const int& x , const int& y, char token, const int& size, int eatMax, bool canClimb)
{
    for(list<Seeded*>::iterator it=seededList.begin(); it != seededList.end(); it++) {
        if((*it)->getPointX()==x && (*it)->getPointY()==y) {
            if((*it)->getSize()<=size || canClimb) {
                if((*it)->getLife() >= eatMax) {
                    (*it)->LoseLife(eatMax);
                    return eatMax;
                }
                else {
                    eatMax = (*it)->getLife();
                    (*it)->LoseLife((*it)->getLife());
                    return eatMax;
                }
            }
        }
    }
    for(list<Seedless*>::iterator it=seedlessList.begin(); it != seedlessList.end(); it++) {
        if((*it)->getPointX()==x && (*it)->getPointY()==y) {
            if(token == 'R' || token == 'G') {
                if((*it)->getToken() != 'A') {
                    if((*it)->getLife() >= eatMax) {
                        (*it)->LoseLife(eatMax);
                        return eatMax;
                    }
                    else {
                        eatMax = (*it)->getLife();
                        (*it)->LoseLife((*it)->getLife());
                        return eatMax;
                    }
                }
            }
            else {
                if((*it)->getLife() >= eatMax) {
                    (*it)->LoseLife(eatMax);
                    return eatMax;
                }
                else {
                    eatMax = (*it)->getLife();
                    (*it)->LoseLife((*it)->getLife());
                    return eatMax;
                }
            }
        }
    }
    return 0;
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

char ecosystem::findPlant(const int& x, const int& y)
{
    std::list<Seeded*>::iterator itD;
    std::list<Seedless*>::iterator itL;

    for(itD = seededList.begin(); itD!=seededList.end(); itD++) {
        if((*itD)->getPointX()==x && (*itD)->getPointY()==y) {
            return (*itD)->getToken();
        }
    }
    for(itL = seedlessList.begin(); itL!=seedlessList.end(); itL++) {
        if((*itL)->getPointX()==x && (*itL)->getPointY()==y) {
            return (*itL)->getToken();
        }
    }

    return '0';
}

void ecosystem::PrintSystem()
{
    cout << endl;
    PrintPlants();
    cout << "Current Plants on the map:" << endl;
    PrintPlantStatistics(); cout << endl;
    cout << "Current Animals on the map:" << endl;
    PrintAnimalStatistics(); cout << endl;
}

void ecosystem::PrintPlantStatistics()
{
    int grass=0, algae=0, oak=0, pine=0, maple=0;

    for(list<Seeded*>::iterator it=seededList.begin(); it != seededList.end(); it++) {
        switch ((*it)->getToken()) {
            case 'O':
                oak++;
                break;
            case 'P':
                pine++;
                break;
            case 'M':
                maple++;
                break;
        }
    }
    for(list<Seedless*>::iterator it=seedlessList.begin(); it != seedlessList.end(); it++) {
        switch ((*it)->getToken()) {
            case 'G':
                grass++;
                break;
            case 'A':
                algae++;
                break;
        }
    }
    cout << "Grass: " << grass << endl;
    cout << "Algae: " << algae << endl;
    cout << "Oak: " << oak << endl;
    cout << "Pine: " << pine << endl;
    cout << "Maple: " << maple << endl;
}

void ecosystem::PrintAnimalStatistics()
{
    int deers=0, rabbits=0, salmon=0, groundog=0, fox=0, wolf=0, bear=0;

    for(list<Carnivore*>::iterator it=carnivoreList.begin(); it != carnivoreList.end(); it++) {
        switch ((*it)->getToken()) {
            case 'F':
                fox++;
                break;
            case 'w':
                wolf++;
                break;
            case 'B':
                bear++;
                break;
        }
    }
    for(list<Herbivore*>::iterator it=herbivoreList.begin(); it != herbivoreList.end(); it++) {
        switch ((*it)->getToken()) {
            case 'D':
                deers++;
                break;
            case 'R':
                rabbits++;
                break;
            case 'G':
                groundog++;
                break;
            case 'S':
                salmon++;
                break;
        }
    }
    cout << "Fox: " << fox << endl;
    cout << "Wolf: " << wolf << endl;
    cout << "Bear: " << bear << endl;
    cout << "Deer: " << deers << endl;
    cout << "Rabbit: " << rabbits << endl;
    cout << "Groundog: " << groundog << endl;
    cout << "Salmon: " << salmon << endl;
}


void ecosystem::PrintMap()
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


void ecosystem::PrintPlants()
{
    char myToken;

    for(int i=0; i < terrainSize; i++) {
        for(int j=0; j < terrainSize; j++) {
            myToken = findPlant(j, i);
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