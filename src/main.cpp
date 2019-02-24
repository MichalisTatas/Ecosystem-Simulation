#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include/classes.h"

using namespace std;


int main(int argc, char const *argv[])
{
    ecosystem* myEcosystem;
    
    srand((int)time(NULL));
    
    myEcosystem = new ecosystem(10, 181);
    myEcosystem->PrintSystem();

    myEcosystem->RunEcosystem(90);
    return 0;
}