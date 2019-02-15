#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../lib/classes.cpp"


int main(int argc, char const *argv[])
{
    ecosystem* myEcosystem;
    
    srand((int)time(NULL));
    
    myEcosystem = new ecosystem(16, 96);
    myEcosystem->PrintSystem();
    return 0;
}