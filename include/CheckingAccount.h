#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "./Account.h"

class CheckingAccount : public Account {
 private:
  static constexpr double overdraftLimit = 500;

 public:
  CheckingAccount(int id, string ownerName, double balance);

  void withdraw(double amount) override;

  void getDetails() override;
};

#endif