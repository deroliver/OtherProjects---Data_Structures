#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include "WaitingQueue.h"
#include "TreatmentQueue.h"
#include "Patient.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include "Random.h"
#include <map>

Random my_random; // Random object

class Simulator {
private:
	TreatmentQueue *treat_Queue; // Treatment queue
	WaitingQueue *wait_Queue; // Waiting queue
	std::vector<std::string> residents; // Holds all the residents names for 273ville


	int clock; // The running clock for the simulator
	double arrivalRate; // The hourly arrival rate entered by the user



public:

	Simulator() : clock(0) {
		// Reads in all the names from the file and puts them in a vector called 'residents'
		std::string name;
		std::ifstream names("residents_273ville.txt");
		while (!names.eof()) {
			names >> name;
			residents.push_back(name);
		}
		// Initialize the Treatment queue and the waiting queue
		treat_Queue = new TreatmentQueue();
		wait_Queue = new WaitingQueue();
	}

	void run_simulation() {
		for (int i = clock; i < 10080; i++){ // Runs for a week worth of minutes
			if (my_random.next_double() < arrivalRate) // Based on the arrival rate
				wait_Queue->Update(i, residents[my_random.random(residents.size() - 1)]); // Runs the waiting queue update function using a random name
			treat_Queue->Update(i); // Treatment queue update function
		}
	}



	void display_records() { // Displays the total patients served
		std::cout << "\nThe emergency room served " << treat_Queue->getTotalTreated() << " patients." << std::endl;
		std::cout << "The total wait time for these patients was " << treat_Queue->getTotalWait() << " minutes." << std::endl; // Total wait time
		std::cout << "The average wait per patient was: " << (treat_Queue->getTotalWait() / static_cast<double>(treat_Queue->getTotalTreated())) << " minutes." << std::endl; // Average wait time

		std::string name;

		bool Exit = true;
		int ex = 0;
		int choice = 0;
		int numP = 0;
		// Displays the menue after the simulator runs
		while (Exit) {
			std::cout << "\n\nMenu" << std::endl;
			choice = read_value("1) List all treated residents\n"  "2) Search for a resident by their name\n", 1, 2);
			switch (choice) {
			case 1:
				for (auto& p : treat_Queue->getRecords()) // Loops through the records map to display all the names that were treated
					std::cout << p.first << std::endl;
				break;

			case 2:
				std::cout << "\nWhat is the name of the resident?" << std::endl;
				std::cin >> name;
				// Counts the amount of times the resident was at the emergency room
				std::cout << std::endl << name << " has been to the emergency room " << treat_Queue->getRecords().count(name) << " times." << std::endl << std::endl; 
				for (auto& p : treat_Queue->getRecords())
					if (p.first == name){ // Finds treated patients based on their name
					std::cout << name << " had a visit with illness " << p.second << std::endl;
					}
				break;

			default:
				std::cout << "Failure\n";
			}
			ex = read_value("\nDo you wish to continue?\n" "For Yes Enter 1\n" "For No Enter 2\n", 1, 2);
			if (ex == 2)
				Exit = false;
		}
	}

	int read_value(const std::string &prompt, int low, int high)
	{
		if (low >= high) // invalid range
			throw std::invalid_argument("invalid range specified");

		std::cin.exceptions(std::ios_base::failbit);
		int num = 0;
		while (true) {
			try {
				while (true) {
					std::cout << prompt;
					std::cin >> num;
					if (num >= low && num <= high) { // within the specified range
						std::cout << std::endl;
						return num;
					}
				}
			}
			catch (std::ios_base::failure) {
				std::cout << "Bad numeric string -- try again\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			}
		}
	}


	void userEnter_data() { // Allows the user to enter the initial settings for the simulator
		treat_Queue->set_waitingQueue(wait_Queue);
		std::cout << "Welcome to My Emergency Room Simulator!" << std::endl;
		std::cout << "Please Answer the Following Questions About the Specifics for Your Simulation!" << std::endl << std::endl;

		int hourlyRate = read_value("Please enter the average patient hourly arrival rate (Between 1 and 59): ", 1, 59);
		arrivalRate = hourlyRate / 60.0;

		int numDoctors = read_value("Please enter the number of doctors: ", 0, INT_MAX);
		int numNurses = read_value("Please enter the number of nurses: ", 0, INT_MAX);


		treat_Queue->setDocs(numDoctors);
		treat_Queue->setNurses(numNurses);

	}

};

#endif