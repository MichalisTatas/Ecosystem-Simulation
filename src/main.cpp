#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <list>
#include "../include/classes.h"

using namespace std;


int main(int argc, char const *argv[])
{
    ecosystem* myEcosystem;
    
    srand((int)time(NULL));
    
    myEcosystem = new ecosystem(16, 1);
    myEcosystem->PrintSystem();
    myEcosystem->RunEcosystem(200);
    return 0;
}