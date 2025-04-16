#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>

using namespace std;

class Account {
 protected:
  double balance;

 public:
  struct TransactionType {
    double amount;
    string type;
    double finalBalance;
  };
  Account(int id, string ownerName, double balance = 0);

  // Must be virtual so it get's trigger when derived class is destroyed
  virtual ~Account();

  Account(const Account& original);

  virtual string getType() = 0;

  virtual void getDetails();

  virtual void withdraw(double amount);

  void save(ostream& out);

  void deposit(double amount);

  void addTransaction(double amount, string type, double finalBalance);

  double getBalance();

  int getId();

 private:
  int id;
  string ownerName;
  int transactionsCount;
  TransactionType* transactions;
};

#endif