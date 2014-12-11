#ifndef CAREGIVER_H_
#define CAREGIVIR_H_

#include "Patient.h"
#include "Random.h"

extern Random my_random;


class CareGiver{
public:
	CareGiver() {} // Constructor

	virtual void Treat(int c, Patient* P) = 0; // Pure virtual method
};



class Doctor : CareGiver {
public:
	Doctor() {} // Constructor

	void Treat(int c, Patient *P) { // Takes integer representing clock and a Patient object
		P->setDoc(true); // Sets Doctor to true
		P->setBeginTreat(c); // Sets begin treatment time
		P->set_treatTime(my_random.random(19) + 1); // Random number between 1 and 20 for treat time

	}
};

class Nurse : CareGiver {
public:
	Nurse() {}

	void Treat(int c, Patient *P) { // Takes integer representing clock and a Patient object
		P->setDoc(false); // Sets Doctor to false
		P->setBeginTreat(c); // Sets begin treatment time
		P->set_treatTime(my_random.random(9) + 1); // Random number between 1 and 10 for treat time



	}


};

#endif