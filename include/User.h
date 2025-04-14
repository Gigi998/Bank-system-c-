#ifndef USER_H
#define USER_H

#include <vector>

#include "./Account.h"

class User {
 private:
  int id;
  string name;
  // holds accounts pointers
  vector<Account*> accounts;

  Account* findAccount(int accountId);

 public:
  User(int id, string name);

  ~User();

  void getDetails();

  void addCheckingAccount(int balance);

  void addSavingsAccount(int balance);

  void removeAccount(int accountId);

  string getName();

  void deposit(int accountId, int amount);

  void withdraw(int accountId, int amount);
};

#endif