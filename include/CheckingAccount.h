#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "./Account.h"

class CheckingAccount : public Account {
 private:
  static constexpr double overdraftLimit = 500;

 public:
  CheckingAccount(int id, string ownerName, double balance);

  void withdraw(double amount);

  void getDetails() override;
};

#endif