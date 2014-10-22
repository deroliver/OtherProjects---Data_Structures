#ifndef SAVINGSACCOUNT_H_
#define SAVINGSACCOUNT_H_
#include "Account.h"
#include <iostream>

class SavingsAccount : public Account
{
public:
	
	/*
	Constructor - Uses the base class Account constructor
	*/
	SavingsAccount(Customer *cust, int acct_number) : Account(cust, acct_number) {}

	/*
	Unique add interest function - Adds interest depending on the type of account
	*/
	void add_interest()
	{
		double amt = balance*customer->get_Savings_Interest(); // Uses the correct type of interest
		balance += amt;
		Transaction *trans = new Transaction(customer->get_account(), "Deposit", amt, get_fees()); // Creates a Transaction object
		transactions.push_back(trans); // Adds the transaction to the transactions of the account
		trans->process_transaction(); // Process the transaction
	}

	/*
	Function to describe the Account:
	Displays the name, customer ID, type of account, current balance, and account ID
	@return A string of the information
	*/
	string to_string()
	{
		stringstream ss;
		ss << "Name: " << customer->get_name() << std::endl;
		ss << "Customer ID: " << customer->get_account() << std::endl;
		ss << "Account Type: Savings" << std::endl;
		ss << "Current Balance: " << balance << std::endl;
		ss << "Account ID: " << account_number << std::endl;
		return ss.str();
	}

};

#endif