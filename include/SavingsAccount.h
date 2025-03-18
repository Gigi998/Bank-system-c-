#include <iostream>
#include <string>

#include "./Account.h"

using namespace std;

class SavingsAccount : public Account {
 private:
  static constexpr int withdrawalLimit = 3;
  static constexpr int minimumBalance = 100;
  static constexpr double interest = 0.05;
  int withdrawalCount;

 public:
  SavingsAccount(int id, string ownerName, int balance);

  void withdraw(int amount);
};