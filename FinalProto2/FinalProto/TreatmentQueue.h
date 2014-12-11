#ifndef TREATMENTQUEUE_H_
#define TREATMENTQUEUE_H_

#include <queue>
#include "Patient.h"
#include "Random"
#include "CareGiver.h"
#include "WaitingQueue.h"
#include <iostream>
#include <map>

extern Random my_random;

class Compare // Compare class for the priority queue
{
public:
	bool operator() (Patient* S1, Patient* S2) { // Compares the treat time of two Patients
		return (S1->get_treatTime() > S2->get_treatTime());
	}

};


class TreatmentQueue
{
private:
	WaitingQueue *waiting;
	std::priority_queue<Patient *, std::deque<Patient *>, Compare> patients; // Patients with the lowest treat time will be at the top of the queue
	std::multimap<std::string, int> records; // Multimap to store all the treated patients and their illness
	Doctor* doctor;
	Nurse* nurse;


	int total_treated;
	int total_wait;

	int num_doctors;
	int num_nurses;
	int docsTreating; // Busy doctors
	int nurseTreating; // Busy nurses

public:
	TreatmentQueue() : docsTreating(0), nurseTreating(0), total_treated(0), total_wait(0) {
		nurse = new Nurse(); // Initialize nurse object
		doctor = new Doctor(); // Initialize doctor object
	}

	// Setter functions for the Treatment queue's member variables
	void setDocs(int docs) {
		num_doctors = docs;
	}

	void setNurses(int nurses) {
		num_nurses = nurses;
	}

	void set_waitingQueue(WaitingQueue *wait) {
		waiting = wait;
	}

	
	// Getter functions for the Treatment queue's member variables
	std::multimap<std::string, int> getRecords() {
		return records;
	}

	int getTotalTreated() {
		return total_treated;
	}

	int getTotalWait() {
		return total_wait;
	}

	int get_numDoctors() {
		return num_doctors;
	}
	int get_numNurses() {
		return num_nurses;
	}
	int get_docsTreating() {
		return docsTreating;
	}

	int get_nurseTreating() {
		return nurseTreating;
	}

	//Treatment queue's update function
	void Update(int clock) {
		if (!waiting->empty()) { // If the size of the waiting queue is not zero
			if ((num_doctors + num_nurses) > (docsTreating + nurseTreating)){ // If there are free doctors or nurses
				Patient *P = waiting->Front(); // Get the patient at the front of the waiting queue
				// The waiting queue is sorted by illness to give priority to those who have a higher illness
				if (P->getIllness() <= 10 && num_nurses > nurseTreating){ // If the Patient's illness is less than or equal to 10, and there are nurses free
					nurseTreating++; // Increase the number of busy nurses
					nurse->Treat(clock, P); 
					patients.push(P); // Push the patient onto the treatment queue
					total_wait += (P->get_beginTreat() - P->get_Arrival()); // Add the waiting period in the waiting queue to the total wait
					waiting->Pop(); // Remove the patient from the watiting queue
				}
				else if (P->getIllness() <= 10 && num_nurses == nurseTreating && docsTreating < num_doctors){ // If the the illess is less than 10, and there are no free nurses, 
					// but there are free doctors
					docsTreating++; // Increase number of busy doctors
					doctor->Treat(clock, P);
					patients.push(P);
					total_wait += (P->get_beginTreat() - P->get_Arrival());
					waiting->Pop();
				}
				else if (P->getIllness() > 10 && docsTreating < num_doctors){ // If the illness is greater than 10, and there are free doctors. Nurses can't treat illness above 10
					docsTreating++; // Increase busy doctors
					doctor->Treat(clock, P);
					patients.push(P);
					total_wait += (P->get_beginTreat() - P->get_Arrival());
					waiting->Pop();
				}
			}
		}
		if (!patients.empty()) { // If the treatement queue is not empty
			// The queue is sorted by treatment time, so the Patient on the top has the shortest treatment time
			
			while (!patients.empty() && clock - patients.top()->get_beginTreat() > patients.top()->get_treatTime()) {// While the patient on top is done being treated
				if (patients.top()->getDoc()) // If a doctor is treating the patient
					docsTreating--; // Free a doctor
				else if (!patients.top()->getDoc()) // If a nurse is treating the patient
					nurseTreating--; // Free a nurse

				records.insert(std::make_pair(patients.top()->get_Name(), patients.top()->getIllness())); // Insert the patient's name and illness in the records multimap
				total_treated++; // Increase total patients treated
				total_wait += patients.top()->get_treatTime(); // Add the patients treat time to the total wait time
				patients.pop(); // Remove the patient because they are done with treatment

			}
		}
	}
};


#endif