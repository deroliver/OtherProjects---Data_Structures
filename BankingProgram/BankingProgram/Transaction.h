#ifndef TRANSACTION_H_
#define TRANSACTION_H_
#include <string>
#include <sstream>


using std::string;
using std::stringstream;

class Transaction
{
private:
	int customer_number; // The customer's number who made the transaction
	string transaction_type; // The type of transaction - Withdrawal or Deposit
	double amount; // The amount that was deposited or withdrawn
	string fees; // A string describing the fees of the transaction
public:
	
	/*
	Constructor - Initialzies all of the values corresponding to the Transaction
	*/
	Transaction(int number, string trans_type, double amt, string fees) : customer_number(number), transaction_type(trans_type), amount(amt), fees(fees) {}
	
	/*
	Displays information about the transaction
	@return A string describing the information about the transaction
	*/
	string process_transaction()
	{
		stringstream ss;
		ss << "\n---------------" << "\nTransaction Type: " << transaction_type << "\nAmount: " << amount << "\n\n   Fees " << fees << "\n---------------";
		return ss.str();
	}

};

#endif