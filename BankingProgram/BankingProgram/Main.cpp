

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Bank.h"
#include "Valid_Input.h"


using namespace std;

/**
This is where we add a new account in the bank
If it is a new customer, we also need to get additional information
to add a new customer record in the bank.

@param bank	Bank object to which we will be adding accounts
*/
void Add_Account(Bank &bank)
{
	string name;
	cout << "Please sign away your soul... I mean enter your name: ";
	cin.ignore();
	getline(cin, name);

	int type;
	stringstream s;
	s << "\n\n----------------" << endl;
	s << "Type of Account: " << endl;
	s << "----------------" << endl << endl;
	s << "---------------------" << endl;
	s << "0 -- Savings Account" << endl;
	s << "---------------------" << endl;
	s << "1 -- Checking Account" << endl;
	s << "---------------------" << endl << endl;
	s << "Enter: ";
	type = Valid_Input(s.str(), 0, 1);
			
	
	
	

	string account_type;
	if (type == 0)
		account_type = "Savings";
	else
		account_type = "Checking";

	Account *acct = bank.add_account(name, account_type); // attempt to add an account
	if (acct == NULL) { // case for new user
		cout << "You appear to be a new user.  We will need more information.\n";
		// get all the required information for a new user
		cout << "\n--------" << endl;
		cout << "Address: ";
		string address;
		cin.ignore();
		getline(cin, address);
		cout << "--------" << endl;
		string telephone;
		cout << "\n-----------------" << endl;
		cout << "Telephone Number: ";
		getline(cin, telephone);
		cout << "-----------------" << endl;

		
		int age;
		std::cin.exceptions(std::ios_base::failbit);
		while (true)
		{
			try {
				cout << "\n----" << endl;
				cout << "Age: ";
				if (cin >> age)
					break;
			}
			catch (std::ios_base::failure)
			{
				std::cout << "\n*Invalid String passed* -- Please Try Again\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			}
		}
		cout << "----" << endl << endl;
		
		int cust_type;
		stringstream s1;
		s1 << "\n-----------------" << endl;
		s1 << "Type of customer: " << endl;
		s1 << "-----------------" << endl << endl;
		s1 << "------------" << endl;
		s1 << "0 -- Adult" << endl;
		s1 << "------------" << endl;
		s1 << "1 -- Senior" << endl;
		s1 << "------------" << endl;
		s1 << "2 -- Student" << endl;
		s1 << "------------" << endl << endl;
		s1 << "Enter : ";
		cust_type = Valid_Input(s1.str(), 0, 2);

		string customer_type;
		if (cust_type == 0)
			customer_type = "Adult";
		else if (cust_type == 1)
			customer_type = "Senior";
		else
			customer_type = "Student";
		acct = bank.add_account(name, address, telephone, age, customer_type, account_type);
	}
	if (acct) {
		cout << "\n\n---------------------------" << endl;
		cout << "Your new account ID is " << acct->get_account_number() << endl;
		cout << "---------------------------" << endl;
	}
	else {
		cout << "Sorry.  We failed to create an account for you\n";
	}
}

/**
The is where we list all the accounts owned by a customer (if he/she exists)

@param bank Bank object in which accounts are located
*/
void List_Account(Bank &bank)
{
	cout << "Please enter your name: ";
	string name;
	cin.ignore();
	getline(cin, name);

	vector<int> list = bank.get_account(name);
	cout << endl;
	for (size_t i = 0; i < list.size(); i++) {
		Account *acct = bank.get_account(list[i]);
		if (acct)
			cout << acct->to_string();
		cout << "---------------------------\n";
	}
	cout << "Total " << list.size() << " accounts found\n";
}

/**
This is where we make a deposit in an account, identified by its account ID

@param bank Bank object in which account is located
*/
void Make_Deposit(Bank &bank)
{
	int acct_id;
	cout << "Please enter your account ID: ";
	cin >> acct_id;
	double amt;
	cout << "Amount to deposit: ";
	cin >> amt;
	bank.make_deposit(acct_id, amt);
}

/**
This is where we make a withdrawal in an account, identified by its ID

@param bank Bank object in which account is located
*/
void Make_Withdrawal(Bank &bank)
{
	int acct_id;
	cout << "Please enter your account ID: ";
	cin >> acct_id;
	double amt;
	cout << "Amount to withdraw: ";
	cin >> amt;
	bank.make_withdrawal(acct_id, amt);
}

int main()
{
	Bank bank; // We create the bank

	// Display menu for banking activites
	cout << "Welcome to the Bank of Derik" << endl;
	cout << "Your Money is in Good Hands" << endl << endl << endl;
	char exit;
	do {
		int choice;
		stringstream s;
		s << "What would you like to do at the bank today?" << endl << endl;
		s << "---------------------------" << endl;
		s << "Enter: 0 -- Add an Account" << endl;
		s << "---------------------------" << endl;
		s << "Enter: 1 -- List Accounts" << endl;
		s << "---------------------------" << endl;
		s << "Enter: 2 -- Make Withdrawal" << endl;
		s << "---------------------------" << endl;
		s << "Enter: 3 -- Make Deposit" << endl;
		s << "---------------------------" << endl;
		s << "Enter: 4 -- Quit" << endl;
		s << "---------------------------" << endl << endl;
		s << "Enter: ";
		choice = Valid_Input(s.str(), 0, 4);
		

		// Perform the banking activity based on the user selection
		switch (choice) {
		case 0:
			Add_Account(bank);
			break;
		case 1:
			List_Account(bank);
			break;
		case 2:
			Make_Withdrawal(bank);
			break;
		case 3:
			Make_Deposit(bank);
			break;
		default:
			cout << "Goodbye!  Thank you for visiting.\n";
			return 0;
		}

		cout << "\n\n------------------------------------------------------" << endl;
		cout << "Do you wish to continue making transactions? (y or n): ";
		cin >> exit;
		cout << "------------------------------------------------------\n\n\n" << endl;
	} while (exit != 'n');

	cout << "Goodbye! Thank you for your money!";
}

	
	
	


	

	

	

	
