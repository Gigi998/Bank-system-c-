#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>

using namespace std;

class Account {
 private:
  struct TransactionType {
    double amount;
    string type;
    double finalBalance;
  };

  int id;
  string ownerName;
  int transactionsCount;
  TransactionType* transactions;

 protected:
  double balance;
  void addTransaction(double amount, string type, double finalBalance);
  void withdraw(double amount);

 public:
  Account(int id, string ownerName, double balance = 0);

  // Must be virtual so the derived class can override it
  virtual ~Account();

  Account(const Account& original);

  void deposit(double amount);

  virtual void getDetails();

  double getBalance();

  int getId();
};

#endif