#ifndef PATIENTQUEUE_H_
#define PATIENTQUEUE_H_

#include <queue>
#include <string>
#include "Patient.h"
#include "Random.h"

class CompareTreat
{
public:
	bool operator() (Patient* S1, Patient* S2) {
		return (S1->get_treatTime() < S2->get_treatTime());
	}

};

class CompareIllness
{
public:
	bool operator() (Patient* S1, Patient* S2) {
		return (S1->getIllness() < S2->getIllness());
	}

};


class PatientQueue {
private:
	std::string name;

public:
	PatientQueue(std::string n) : name(n) {}

	std::string get_queue_name() const {
		return name;
	}

	void check_arrival(int clock) {}




};


class TreatmentQueue : PatientQueue {
private:
	WaitingQueue* waiting;
	std::priority_queue<Patient *, std::vector<Patient*>, CompareTreat> patients;

	int total_treated;
	int total_wait;

	int num_doctors;
	int num_nurses;
	int docsTreating;
	int nurseTreating;

public:
	TreatmentQueue(std::string name) : PatientQueue(name) {}

	void set_waitingQueue(WaitingQueue * wait) {
		waiting = wait;
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

	int RandTreatTime(int n) {
		Random R;
		return R.random(n);
	}



	void Update(int clock) {
		if (waiting->getSize() != 0) {
			if ((num_doctors + num_nurses) > (patients.size() + 1)){
				Patient * P = waiting->Front();
				if (P->getIllness() <= 10 && num_nurses > nurseTreating){
					nurseTreating++;
					P->setBeginTreat(clock);
					P->setDoc(false);
					P->set_treatTime(RandTreatTime(10));
					patients.push(P);
					waiting->Pop();
				}
				else if (P->getIllness() <= 10 && num_nurses == nurseTreating && docsTreating < num_doctors){
					docsTreating++;
					P->setBeginTreat(clock);
					P->setDoc(true);
					P->set_treatTime(RandTreatTime(20));
					patients.push(P);
					waiting->Pop();
				}
				else if (P->getIllness() > 10 && docsTreating < num_doctors){
					docsTreating++;
					P->setBeginTreat(clock);
					P->setDoc(true);
					P->set_treatTime(RandTreatTime(20));
					patients.push(P);
					waiting->Pop();
				}
			}
		}
		if (!patients.empty()) {

		}


	}


};

class WaitingQueue : PatientQueue {
private:
	std::priority_queue<Patient *, std::vector<Patient*>, CompareIllness> patients;
	int totalWait;
	int numServed;
public:
	WaitingQueue(std::string name) : PatientQueue(name) {}

	void Update(int clock, std::string name) {
		Patient* P = new Patient(clock, name);
		patients.push(P);
	}

	int get_numServed() {
		return numServed;
	}

	int get_totalWait() {
		return totalWait;
	}

	int getSize() {
		return patients.size();
	}

	Patient* Front() {
		return patients.front();
	}

	void Pop() {
		patients.pop();
	}

};




#endif