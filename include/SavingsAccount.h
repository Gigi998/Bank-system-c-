#include <iostream>
#include <string>
#include <thread>

#include "./Account.h"

using namespace std;

class SavingsAccount : public Account {
 private:
  static constexpr int withdrawalLimit = 3;
  static constexpr int minimumBalance = 100;
  static constexpr double interest = 0.05;
  int withdrawalCount;

  // Interest thread
  thread interestThread;

  void addInterests();

 public:
  SavingsAccount(int id, string ownerName, double balance);

  ~SavingsAccount();

  void withdraw(double amount);
};