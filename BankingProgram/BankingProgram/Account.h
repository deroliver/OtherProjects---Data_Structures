#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include "Customer.h"
#include "Transaction.h"
#include <vector>
#include <sstream>
#include <string>

using std::vector;
using std::stringstream;
using std::string;

class Account
{
protected:
	Customer * customer; // The customer object - Owns the account
	double balance; // The dollar balance of the account
	int account_number; // The unique account number of this account
	vector<Transaction*> transactions; // A vector of all previous transaction objects
	
	/*
	Describes the fees associated with the account.
	The fees vary depending on the type of customer.
	Returns a string that contains the description of the fees.
	*/
	string get_fees() {
		double overdraft, check_charge;

		overdraft = customer->get_Overdraft(); // Uses polymorphism to call the correct function depending on the customer type
		check_charge = customer->get_Check_Charge(); // Uses polymorphism to call the correct function depending on the customer type
		
		stringstream ss;
		ss << "\nCheck Charge: " << check_charge << "\nOverdraft Charge: " << overdraft;
		return ss.str();
	}
	
	
	/*
	Adds interest to the account based on the value passed
	Parameter - amount of interest to add
	*/
	void add_interest(double interest){
		double amt = balance*interest; // Calculate the amount of interest
		balance += amt; // Add the interest to the balance
		string fees = get_fees(); // Get the fees
		Transaction *tran = new Transaction(customer->get_account(), "Deposit", amt, get_fees()); // Create a transaction object for the interest deposit
		transactions.push_back(tran); // Add the Transaction object to the transactions vector for the account
	}

public:
	
	/*
	Constructor for an Account, requires a customer object
	Balance will always start at 0
	*/
	Account(Customer* cust, int id) : customer(cust), account_number(id), balance(0) {}

	/*
	Returns the customer associated with this account
	*/

	Customer *get_customer()
	{
		return customer;
	}

	/*
	Sets the customer who owns this account
	*/
	void set_customer(Customer *cust)
	{
		customer = cust;
	}

	/*
	Gets the account number for the Account
	*/
	int get_account_number()
	{
		return account_number;
	}

	/*
	Sets the account number for the Account
	*/
	void set_account_number(int id)
	{
		account_number = id;
	}

	/*
	Gets the balance of the Account
	*/
	double get_balance()
	{
		return balance;
	}

	/*
	Sets the balance of the Account
	*/
	void set_balance(double new_balance)
	{
		balance = new_balance;
	}

	/*
	Describes the account information

	The derived classes 'CheckingAccount' and 'SavingsAccount' Also implement this function
	These classes also specify the type of account
	This Base Class 'Account' does not need to define this function, since an Account has to be a Checking or Savings account
	So we can make this function a pure virtual function
	*/
	virtual string to_string() = 0;
	
	/*
	A function for depositing money in the account
	This function does not depend on the type of Account, so we can define this function in the base class
	*/
	void deposit(double amt)
	{
		balance += amt;
		Transaction *trans = new Transaction(customer->get_account(), "Deposit", amt, get_fees());
		transactions.push_back(trans);
		std::cout << trans->process_transaction() << std::endl;
	}
	
	/*
	A function for withdrawing money in the account
	This function does not depend on the type of Account, so we can define this function in the base class
	*/
	void withdraw(double amt)
	{
		balance -= amt;
		Transaction *trans = new Transaction(customer->get_account(), "Withdrawal", amt, get_fees());
		transactions.push_back(trans);
		std::cout << trans->process_transaction() << std::endl;
	}

	/*
	A function for adding interest to the account
	The amount of interest depends on the type of account, so we define this function in the derived classes
	*/
	virtual void add_interest() = 0;
	


};

#endif