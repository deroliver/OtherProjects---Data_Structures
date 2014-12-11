#include "Simulator.h"
#include <iostream>
#include <fstream>

int main(){
	Simulator S1;
	S1.userEnter_data();
	S1.run_simulation();
	S1.display_records();	
}