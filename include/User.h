#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>

#include "./Account.h"

using namespace std;

class User {
 private:
  int id;
  string name;
  vector<Account*> accounts;

 public:
  User(int id, string name);

  ~User();

  void getDetails();

  void addCheckingAccount(int balance);

  void addSavingsAccount(int balance);

  // void removeAccount(int accountId);

  string getName();
};

#endif