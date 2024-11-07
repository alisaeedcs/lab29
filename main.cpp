//include necessary headers for file handling, dat structures, etc.
#include <iostream>
#include <map>
#include <list>
#include <array>
#include <string>
#include <fstream>
using namespace std;

//define a function ot simulate valet parking over time


void simulate(map<int, array<list<string>, 3>>& garage, int trials);
//parameters:
// map of parking garage floors, and num of trials u want it to simulate for (>25)

//define main function
int main() {
    srand(time(0)); //seed random time
    //initialize a map to store parking garage levels, and each to be associated with array of lists for arrival time, the cars that are parked, and available parking spaces
    map<int, array<list<string>, 3>> garage;
    // element 0 in array: list 0 will include cars that have parked on that floor
    // element 1 in array: list 1 will include arrival times of the cars on the floor
    // element 2 in array: list 2 will show available spaces on that floor by identification 

    //open an external file and 
    //ifstream fin("data.txt");
    //if (!fin) {
        //cout << "Invalid external file!" << endl;
        //return 0;
  //  }
};


