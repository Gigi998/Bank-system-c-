#include "./include/Account.h"

#include <iostream>
#include <string>

using namespace std;

Account::Account(int id, string ownerName, int balance) {
  this->id = id;
  this->balance = balance;
  this->ownerName = ownerName;
  this->transactionsCount = 0;
  this->transactions = new TransactionType[transactionsCount];
}

Account::~Account() {
  cout << "Destructor" << endl;
  delete[] transactions;
  transactions = nullptr;
}

// Copy constructor
Account::Account(const Account& original) {
  this->id = original.id;
  this->balance = original.balance;
  this->ownerName = original.ownerName;
  this->transactionsCount = original.transactionsCount;
  // Must create new dynamic array
  TransactionType* transactions = new TransactionType[transactionsCount];
  // Copy values from original
  for (int i = 0; i < transactionsCount; i++) {
    transactions[i].amount = original.transactions[i].amount;
    transactions[i].type = original.transactions[i].type;
    transactions[i].finalBalance = original.transactions[i].finalBalance;
  }

  this->transactions = transactions;
}

// PRIVATE
void Account::addTransaction(int amount, string type, int finalBalance) {
  // Create new transactions dynamic array
  TransactionType* newTransactions = new TransactionType[transactionsCount + 1];

  // Copy old transactions
  for (int i = 0; i < transactionsCount; i++) {
    newTransactions[i].amount = (*(transactions + i)).amount;
    newTransactions[i].type = (*(transactions + i)).type;
    newTransactions[i].finalBalance = (*(transactions + i)).finalBalance;
  }

  // Add newly created trans
  newTransactions[transactionsCount].amount = amount;
  newTransactions[transactionsCount].type =
      type == "deposit" ? "deposit" : "withdraw";
  newTransactions[transactionsCount].finalBalance = finalBalance;

  // Dellocate memory
  delete[] transactions;

  // Assign new transcation array
  transactions = newTransactions;

  transactionsCount++;
}

// PUBLIC
void Account::getDetails() {
  cout << "Account number is: " << id << ", owner is: " << ownerName << endl;

  cout << "Transactions" << endl;

  cout << "--------------" << endl;

  for (int i = 0; i < transactionsCount; i++) {
    cout << "Type: " << (*(transactions + i)).type
         << ", Amount: " << (*(transactions + i)).amount
         << ", Final Balance: " << (*(transactions + i)).finalBalance << endl;
  }

  cout << "--------------" << endl;
}

void Account::deposit(int amount) {
  this->balance += amount;

  addTransaction(amount, "deposit", balance);
}

void Account::withdraw(int amount) {
  if (this->balance > amount) {
    this->balance -= amount;
    addTransaction(amount, "withdraw", balance);
  } else {
    cout << "Insuficient balance" << endl;
    addTransaction(0, "failed withdraw", balance);
  }
}

int Account::getBalance() { return balance; }