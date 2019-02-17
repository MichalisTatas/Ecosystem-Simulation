#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <list>
// #include "../lib/plants.cpp"
#include "../include/classes.h"
//#include "../include/point.h"

using namespace std;


int main(int argc, char const *argv[])
{
    ecosystem* myEcosystem;
    
    srand((int)time(NULL));
    
    myEcosystem = new ecosystem(16, 96);
    myEcosystem->PrintSystem();
    return 0;
}