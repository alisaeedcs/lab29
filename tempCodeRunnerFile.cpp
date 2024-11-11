// comsc-210 | ali saeed \ lab 29 alpha
//ide used: vs code
//think that i implemented the wireframe and the pseudocode well without going to into it while still giving a demo
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
    ifstream fin("data.txt");
    if (!fin) {
        cout << "Invalid external file!" << endl;
		return 0;
    } //if file does not open print error and exit

  //here we will read the file that will contain 3 floors with some data of cars that are already parked and all the parking spaces /capacity
	int floor = 0;
	string input;
	array<list<string>, 3> floorOne, floorTwo, floorThree;
	int i = 0;


	//added  working file input into file
	while (getline(fin, input)) {
		if (input.length() >= 6) {
			if (input.substr(0,5) == "Floor") {
				if (input.substr(6) == "One") {
					floor = 1;
				}
				if (input.substr(6) == "Two") {
					floor = 2;
				}
				if (input.substr(6) == "Three") {
					floor = 3;
				}
			}
		}
		else if (floor == 1) {
			if (input == "A1" || input == "A2" || input == "A3" || input == "A4" || input == "A5") {
				floorOne[0].push_back(input); // our unavailable spaces
			}
			else if (input.substr(0,2) == "42") {
				floorOne[1].push_back(input); // our arrival times
			}
			else {
				floorOne[2].push_back(input); // our available spaces
			}
		}
		else if (floor == 2) {
			floorTwo[2].push_back(input); // all spaces are available on floor 2
		}
		else if (floor == 3) {
			floorThree[2].push_back(input); // all spaces are available on floor three
		}
	}

	// ideally we would close the file after reading in from the file
	fin.close();

	garage[1] = floorOne;
	garage[2] = floorTwo;
	garage[3] = floorThree;

	//begin time based simulation for valet updates
	simulate(garage, 15); // 3 trials so 30 minutes passing from 7 am
	//will use the simulate function definition to operate

	return 0; //end of main function

};


//function definitiion
void simulate(map<int, array<list<string>, 3>>& garage, int trials) {
	//output initial status of garage
	cout << "Initial state of parking garage:\n";
	output(garage);

	int start_time = 60 * 7; //get the starting time in minutes  ( 7 am)
	list<string> waiting;


	//starts at 7 am
	//start the amount of intervals
	for (int i = 0; i < trials; i++) {
		int current_time = start_time + ((i + 1) * 10); // current time from 7 am so the firt one would be 10 + start_time
		cout << (i + 1)  * 10 << " Minutes In: \n"; //output the amount of time we are in

		int carArrivals = rand() % 25; //number of arrivals supposed to be 10 but for now we do 7 for dummy test
		int carRetrievals = rand() % 2; //^ same for this it supposed to be 5 for dummy we do 1



		//handle car retrievals
		for (int k = 0; k < carRetrievals; k++) {
			for (auto &floor: garage) { //for each floor in teh garage
				//for sum clarity
				//floor.second[0] contains the occupied spaces
				//floor.second[1] contains the arrival times
				//floor.second[2] contains the available spaces

				if (!floor.second[0].empty()) { //if the parked cars list is not empty on that floor
					//would do random but for now do the first car
					string parking_id = floor.second[0].front(); //set the car we retrieve to the first car in tat list to string
					floor.second[0].pop_front(); //get rid of it from that list
					int car_time = current_time - stoi(floor.second[1].front()); // get the int time of how long its been in minutes
					int hours = car_time / 60; //get num of hours theyve been parked
					int minutes = car_time % 60; //get num of minutes theyve been parked
					floor.second[1].pop_front(); //time at same index of the car parking id
					floor.second[2].push_back(parking_id); //put that space id in available now last 
					cout << "\tCar retrieved from space " << parking_id << " on Floor: " << floor.first << ". Car was parked for " << hours << " hours and " << minutes << " minutes.\n"; //output in nice ofrmatting
					break; //exit this loop since weve received that first car 
				}
				else {
					cout << "\tNo cars parked" << endl; 
					//check other floors if this is true
				}
				//will add ability to check for others
			}
		}


		//check if any cars are in the queue (prioritize parking them if the)
		if (!waiting.empty()) {
			for (auto it = waiting.begin(); it != waiting.end();) {
				bool spot_found = false;

				for (auto &floor: garage) {
					if (!floor.second[2].empty()) {
						string parking_id = floor.second[2].front();
						floor.second[2].pop_front();
						floor.second[0].push_back(parking_id);
						floor.second[1].push_back(to_string(current_time)); 
						it = waiting.erase(it); //moves iterator to next increment
						spot_found = true; 
						cout << "\tCar in waiting line parked in space " << parking_id << " on Floor: " << floor.first << endl; 
						break;
					}
				}
				if (!spot_found) {
					cout << "\tNo space found for waiting cars, wait for next interval\n";
					break;
				}
			}

		}
		//handle car arrivals
		if (waiting.size() > 4) {
			cout << "\tLine of cars waiting is full. No new car arrivals at this time\n";
		}
		else {
			for (int j = 0; j < carArrivals; j++) {
				bool car_parked = false; //bool for car parked

				//try parking on each floor starting with the first floor
				for (auto &floor: garage) {
					//check if there is available space on the floor
					if (!floor.second[2].empty()) {
						//if there is
						//set the parking space we wil take to the first one on the list of the available
						string parking_id = floor.second[2].front();
						//get rid of the id from being the available list
						floor.second[2].pop_front();
						//add our parking id to the ones that cars are parked at
						floor.second[0].push_back(parking_id);
						//put the current time in the list
						floor.second[1].push_back(to_string(current_time)); //time in minutes since like 12 am or whateber so 7 am plus the time it got added
						//will add other conditions if this is full later (if i have to)
						car_parked = true; // make it so that the car is parked
						cout << "\tCar parked in space " << parking_id << " on Floor: " << floor.first << endl; 
						break;
					}
				}
				if (!car_parked) {
					//if it was not set to true and there was no space at all the car will wait
					if (waiting.size() < 5) {
						waiting.push_back("Car waiting");
						cout << "\tNo space for car, it is waiting outside\n";
					}
					else {
						cout << "\tWaiting line full\n";
						break;
					}
					//code to add it to a queue where when space empties it will be added
				}
			}
			cout << "\n";
		}
		output(garage); //output once more
	}
}

//output the map of the garage definition
void output(map<int, array<list<string>, 3>>& garage) {
	//method i chose to output
	for (const auto &floor: garage) { //for each floor
		cout << "Floor " << floor.first << endl; //first output the floor number
		cout << "\tNumber of Cars Parked " << floor.second[0].size() << endl; //then output the numbers of cars parked on that floor
		cout << "\tNumber of Available Spaces " << floor.second[2].size() << endl; //then the available remaining spaces on that floor
	}
	cout << endl;
}