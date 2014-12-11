#ifndef WAITINGQUEUE_H_
#define WAITINGQUEUE_H_

#include "Patient.h"
#include <queue>
#include <string>
#include <list>


extern Random my_random;



class CompareIllness // Compares the illness of two Patients
{
public:
	bool operator() (Patient* S1, Patient* S2) {
		return (S1->getIllness() < S2->getIllness());
	}

};


class WaitingQueue {
private:
	std::priority_queue<Patient *, std::deque<Patient*>, CompareIllness> patients; // Priority queue that puts patients with the highest illness at the top

public:

	WaitingQueue() {}

	void Update(int clock, std::string name) {
		Patient* P = new Patient(clock, name); 
		patients.push(P); // Pushes a new patiens onto the waiting queue
	}
	
	bool empty() {
		return patients.empty();
	}

	Patient* Front() {
		return patients.top();
	}

	void Pop() {
		patients.pop();
	}

};


#endif