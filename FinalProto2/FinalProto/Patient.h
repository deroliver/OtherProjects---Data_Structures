#ifndef PATIENT_H_
#define PATIENT_H_

#include <string>
#include "Random.h"

extern Random my_random; // Random object

class Patient {
private:
	int arrivalTime; // When the patient arrives at the wait queue
	int beginTreatment; // When the patient begins treatment
	int endTreatment; // When the patient ends treatment
	int illness; // The patients level of illness
	int treatTime; // The time it is going to take to treat the patient
	bool Doctor; // If true, patient is being treated by a doctor
	std::string name; // Patient's name

public:
	// Initialize the patient, also assign them an illness automatically
	Patient(int clock, std::string name) : arrivalTime(clock), name(name), beginTreatment(0), endTreatment(0), treatTime(0) {
		int r = my_random.random(10) + 1;
		if (r <= 7)
			illness = my_random.random(9) + 1;

		else if (r > 7 && r <= 9)
			illness = my_random.random(14) + 1;

		else if (r == 10)
			illness = my_random.random(19) + 1;
	}


	// Getter function for Patient's member variables
	int getIllness(){
		return illness;
	}

	int get_Arrival() {
		return arrivalTime;
	}

	std::string get_Name() {
		return name;
	}

	int get_treatTime() {
		return treatTime;
	}

	int get_beginTreat() {
		return beginTreatment;
	}

	bool getDoc() {
		return Doctor;
	}

	
	// Setter function for Patient's member variables
	void setArrival(int v) {
		arrivalTime = v;
	}

	void setDoc(bool doc){
		Doctor = doc;
	}

	void setBeginTreat(int c) {
		beginTreatment = c;
	}

	void set_treatTime(int c) {
		treatTime = c;
	}
};

#endif
