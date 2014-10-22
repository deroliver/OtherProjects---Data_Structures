#ifndef SENIORCUST_H_
#define SENIORCUST_H_
#include "Customer.h"

class SeniorCustomer : public Customer
{
public:
	
	/*
	Constructor for an Adult Customer, uses the contructor from the Customer base class
	*/
	SeniorCustomer(string name, string address, string telephone, int age, int cust_numb) : Customer(name, address, telephone, age, cust_numb)
	{}
	
	/*
	Functions to get the values of the charges, these are unique to the Adult customer class
	*/
	double get_Overdraft()
	{
		return OVERDRAFT_CHARGE;
	}
	double get_Savings_Interest()
	{
		return SAVINGS_INTEREST;
	}
	double get_Check_Interest()
	{
		return CHECK_INTEREST;
	}
	double get_Check_Charge()
	{
		return CHECK_CHARGE;
	}

private:
	
	/*
	Unique values of the charges for the Adult customer
	*/
	const double SAVINGS_INTEREST = .6;
	const double CHECK_INTEREST = .2;
	const double CHECK_CHARGE = 3;
	const double OVERDRAFT_CHARGE = 10;
};

#endif