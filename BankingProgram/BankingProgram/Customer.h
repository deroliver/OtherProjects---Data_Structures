#ifndef CUSTOMER_H_
#define CUSTOMER_H_
#include <string>

using std::string;

class Customer
{
protected:
	string name; // The name of the Customer
	string address; // The address of the Customer
	int age; // The Customer's age
	string telephone_number; // The Customer's telephone number
	int customer_number; // The Customer's unique customer number

public:
	
	/*
	Constructor - Initialized all of the information about the customer
	*/
	Customer(string name, string addresss, string telephone, int age, int cust_numb) : name(name), address(address), telephone_number(telephone), age(age), 
		customer_number(cust_numb) {}

	/*
	Pure virtual function that will be defined in the derived classes
	We can use polymorphism, so the Customer object will call the correct function and in turn return the correct fees, and interest
	*/
	virtual double get_Overdraft() = 0;
	virtual double get_Savings_Interest() = 0;
	virtual double get_Check_Interest() = 0;
	virtual double get_Check_Charge() = 0;
	
	/*
	Accessors and Modifiers for all the information about the Customer
	*/
	void set_name(string new_name)
	{
		name = new_name;
	}
	string get_name()
	{
		return name;
	}

	void set_address(string new_address)
	{
		address = new_address;
	}
	string get_address()
	{
		return address;
	}

	void set_age(int new_age)
	{
		age = new_age;
	}
	int get_age()
	{
		return age;
	}

	void set_telephone(string new_telephone)
	{
		telephone_number = new_telephone;
	}
	string get_telephone()
	{
		return telephone_number;
	}

	void set_account(int new_account)
	{
		customer_number = new_account;
	}
	int get_account()
	{
		return customer_number;
	}

};

#endif