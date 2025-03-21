#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include <thread>

#include "./Account.h"

class SavingsAccount : public Account {
 private:
  int withdrawalCount;

  // Interest thread
  thread interestThread;
  // Stop thread, must have a way to stop the thread otherwise it will run
  // forever
  bool stopThread;

  void addInterests();

 public:
  static constexpr int withdrawalLimit = 3;
  static constexpr double interest = 0.05;
  static constexpr int minimumBalance = 100;

  SavingsAccount(int id, string ownerName, double balance);

  ~SavingsAccount();

  void withdraw(double amount) override;

  void getDetails() override;
};

#endif