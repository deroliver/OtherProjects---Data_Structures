#ifndef BANK_H_
#define BANK_H_
#include "Account.h"
#include "Customer.h"
#include "StudentCust.h"
#include "SeniorCust.h"
#include "AdultCust.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"
#include <string>
#include <vector>


using std::vector;
using std::iterator;
using std::string;

class Bank
{
private:
	vector<Account*> accounts; // Vector that holds all the accounts in the bank
	vector<Customer*> customers; // Vector that holds all the customers in the bank
	
	int account_id; // Value used to generate unique account id
	int customer_id; // Value used to generate unique customer id

	/*
	Returns a vector of account numbers that are owned by the passed name
	@param name The name of the customer to search for
	@return a vector<int> with the account IDs corresponding to the name
	*/
	vector<int> find_accounts_by_name(string name)
	{
		vector<int> user_accounts;
		for (int i = 0; i < accounts.size(); i++) // Loop through the vector of Bank accounts
		{
			if (this->accounts[i]->get_customer()->get_name() == name) // Check for a matching name
				user_accounts.push_back(accounts[i]->get_account_number()); // Add the corresponding account number to the vector
		}
		return user_accounts; // Return the vector of account numbers

	}

	/*
	Searches through all the customers in the customer vector
	If the name is found - a pointer to that customer if returned
	If not, NULL is returned
	@param name The name of the customer to search for
	@return If the name is found - A pointer to the Customer; If not found - NULL
	*/
	Customer* find_customer(string name)
	{
		for (int i = 0; i < customers.size(); i++) // Loop through the vector of customers
		{
			if (customers[i]->get_name() == name) // Check for a matching name amongst the customers
				return customers[i]; // Return the matching customer
		}
		return NULL;
	}

	/*
	Adds a new account corresponding to a Customer - The account type is specified
	@param cust The customer who is going to own the account
	@param account_type The type of account to create
	@return Pointer to the new account created
	*/
	Account* add_account(Customer* cust, string account_type)
	{
		account_id++; // Increment account_id
		Account *Acct;
		if (account_type == "Checking") // Check if the account type is Checking
		{
			Acct = new CheckingAccount(cust, account_id); // If Checkig create a dynamic CheckingAccount object 
		}
		else
		{
			Acct = new SavingsAccount(cust, account_id); //If no Checkig create a dynamic SavingsAccount object 
		}

		accounts.push_back(Acct);
		return Acct;
	}

public:
	/*
	Constructor for the Bank
	*/
	Bank() : account_id(1000), customer_id(1000) {}


	/*
	This adds an account for an existing customer
	@param name The customers name
	@param account_type The type of account
	@return Pointer to the created account if the Customer exists; If not - NULL
	*/
	Account* add_account(string name, string account_type)
	{
		Customer *cust = find_customer(name); // Create a new customer, if the name corresponds to a current customer, set it equal to the new customer
		if (cust == NULL) // If the name is not found
			return NULL; // Return NULL
		return add_account(cust, account_type); // Else the name is found -- return a newly created account
	}

	/*
	This adds an account for a new Customer
	@param name The customer's name
	@param address The customer's address
	@param telephone The customer's telephone
	@param age The customer's age
	@param cust_type The customer's type - Adult, Senior, or Student
	@param account_type The account type - Checking or Savings
	@return Pointer to the newly created Account
	*/
	Account * add_account(string name, string address, string telephone, int age, string cust_type, string account_type)
	{
		Customer *cust; // Create a pointer to a Customer object
		customer_id++; // Increment customer id, since we are going to add a customer 
		if (cust_type == "Student") // If the type if Student
			cust = new StudentCustomer(name, address, telephone, age, customer_id); // Set cust equal to a dynamically created Student customer object
		
		else if (cust_type == "Senior") // If the type is Senior
			cust = new SeniorCustomer(name, address, telephone, age, customer_id); // Set cust equal to a dynamically created Senior customer object
		
		else // Else the type must be Adult
			cust = new AdultCustomer(name, address, telephone, age, customer_id); // Set cust equal to a dynamically created Adult customer object

		customers.push_back(cust); // Add the Customer object to the vector of Customers in the bank
		return add_account(cust, account_type); // Return a pointer to the new account created, and add the account to the Bank
	}

	/*
	Makes a deposit in the specified account
	@param acct_number The account number to make the deposit in
	@param amt The amount of money to deposit
	@return void
	*/
	void make_deposit(int acct_number, double amt)
	{
		Account *Acct = get_account(acct_number); // Search for an account corresponding to the account number passed
		if (Acct) // If Acct is found, not NULL
		{
			Acct->deposit(amt); // Deposit the money using the Account member function
		}
	}

	/*
	Makes a withdrawal from the specified account
	@param acct_number The account number make the withdrawal from
	@param amt The amount of money to withdraw
	@return void
	*/
	void make_withdrawal(int acct_number, double amt)
	{
		Account *Acct = get_account(acct_number); // Search for an account corresponding to the account number passed
		if (Acct) // If Acct is found, not NULL
		{
			Acct->withdraw(amt); // Withdraw the money using the Account member function
		}
	}

	/*
	Get all the account associated with a Customer by his/her name
	@param name The name of the customer
	@return A vector of account numbers corresponding to the name passed
	*/
	vector<int> get_account(string name)
	{
		return find_accounts_by_name(name); // Call the find_accounts_by_name function to return a vector of all accounts assosiated with the name
	}

	/*
	Gets an account corresponding to an account number
	@param acct_number The account number to search for
	@return A pointer to an account corresponding to the account number
	*/
	Account *get_account(int acct_number)
	{
		for (int i = 0; i < accounts.size(); i++) // Loop through the vector of accounts
		{
			if (accounts[i]->get_account_number() == acct_number) // If the account is found with the account number
				return accounts[i]; // return the correspondnig account
		}
		return NULL; // Else return NULL
	}

};

#endif