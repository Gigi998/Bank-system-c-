#include "./include/Account.h"

Account::Account(int id, string ownerName, double balance) {
  this->id = id;
  this->balance = balance;
  this->ownerName = ownerName;
  this->transactionsCount = 0;
  this->transactions = new TransactionType[transactionsCount];
  addTransaction(this->balance, "Account opened", getBalance());
}

Account::~Account() {
  cout << "Account Destructor" << endl;
  delete[] transactions;
  transactions = nullptr;
}

// Copy constructor
Account::Account(const Account& original) {
  cout << "copy" << endl;
  this->id = original.id;
  this->balance = original.balance;
  this->ownerName = original.ownerName;
  this->transactionsCount = original.transactionsCount;
  // Must create new dynamic array
  TransactionType* newTransactions = new TransactionType[transactionsCount];
  // Copy values from original
  for (int i = 0; i < transactionsCount; i++) {
    newTransactions[i].amount = original.transactions[i].amount;
    newTransactions[i].type = original.transactions[i].type;
    newTransactions[i].finalBalance = original.transactions[i].finalBalance;
  }

  this->transactions = newTransactions;
}

// PRIVATE
void Account::addTransaction(double amount, string type, double finalBalance) {
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
  newTransactions[transactionsCount].type = type;
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

  cout << "TRANSACTIONS" << endl;

  cout << "--------------" << endl;

  for (int i = 0; i < transactionsCount; i++) {
    cout << (*(transactions + i)).type
         << ", Amount: " << (*(transactions + i)).amount
         << ", Final Balance: " << (*(transactions + i)).finalBalance << endl;
  }

  cout << "--------------" << endl;
}

void Account::deposit(double amount) {
  this->balance += amount;
  cout << "Deposit successfull" << endl;
  addTransaction(amount, "Deposit", balance);
}

void Account::withdraw(double amount) {
  this->balance -= amount;
  cout << "Withdraw successfull" << endl;
  addTransaction(amount, "Withdraw", balance);
}

double Account::getBalance() { return balance; }

int Account::getId() { return id; }

void Account::save(ostream& out) {
  out << "Balance: " << getBalance() << endl;

  out << "Transactions" << endl;

  for (int i = 0; i < transactionsCount; i++) {
    out << "Amount: " << (*(transactions + i)).amount
        << ", " + (*(transactions + i)).type
        << ", Final Balance: " << (*(transactions + i)).finalBalance << endl;
  }
}