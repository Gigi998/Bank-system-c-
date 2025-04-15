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

 public:
  void save(ostream& out);

  Account(int id, string ownerName, double balance = 0);

  virtual void getDetails();

  virtual void withdraw(double amount);

  // Must be virtual so it get's trigger when derived class is destroyed
  virtual ~Account();

  Account(const Account& original);

  void deposit(double amount);

  double getBalance();

  int getId();
};

#endif