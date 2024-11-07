//include necessary headers for file handling, dat structures, etc.
#include <iostream>
#include <map>
#include <list>
#include <array>
#include <string>
#include <fstream>
using namespace std;

//define a function ot simulate valet parking over time
void simulate(map<int, array<list<string>, 3>>&, int);
//parameters:
// map of parking garage floors, and num of trials u want it to simulate for (>25)

//outputs the parking garage status
void output(map<int, array<list<string>, 3>>&);
//parameters:
// map of parking garage floors

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
  //  } if file does not open print error and exit
	
	//instead for wireframe just make a dumy one
	int floor = 1;
	array<list<string>, 3> floorOne;
	floorOne[0].push_back("A1"); //place car is parked in
	floorOne[1].push_back("1.00"); // at 8 am, sims start at 7 am if it was at like 8:30 we would do 1.30
	floorOne[2].push_back("A2, A3, A4"); //these parking spaces are available

	garage[floor] = floorOne; // populate the map

	// close the file
	//fin.close();

	//begin time based simulation for valet updates

};


//function definitiion
void simulate(map<int, array<list<string>, 3>>& garage, int trials) {
	//output initial status of garage
	cout << "Initial state of parking garage:\n";
	output(garage);

	for (int i = 0; i < trials; i++) {
		cout << (i + 1)  * 10 << " Minutes In: \n";

		int carArrivals = rand() % 11; //number of arrivals

		if (garage[0].second[1].size() != 1)
		
	}
}

void output(map<int, array<list<string>, 3>>& garage) {
	for (const auto &floor: garage) {
		cout << "Floor " << floor.first << endl;
		cout << "\tNumber of Cars Parked " << floor.second[0].size() << endl;
		cout << "\tNumber of Available Spaces " << floor.second[2].size() << endl;
}