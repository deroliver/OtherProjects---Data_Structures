#ifndef RANDOM_H_
#define RANDOM_H_

#include <ctime>
#include <cstdlib>


class Random { // Random class, taken from the book
public:
	Random(){
		srand((unsigned int)std::time(0));
	}

	Random(int seed){
		srand(seed);
	}

	double next_double(){
		return double(rand()) / RAND_MAX;
	}

	int random(int n){
		return int(next_double() * n);
	}

};


#endif