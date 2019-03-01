#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "../include/classes.h"

using namespace std;


int main(int argc, char const *argv[])
{
    string numOfDays;
    ecosystem* myEcosystem;
    
    srand((int)time(NULL));
    
    myEcosystem = new ecosystem(10, 180);
    // myEcosystem->PrintMap();

    cout << "Enter the number of days you wish the program to run for!" << endl;
    getline(cin, numOfDays);

    myEcosystem->RunEcosystem(atoi(numOfDays.c_str()));
    return 0;
}