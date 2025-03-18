#include "./include/SavingsAccount.h"

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

SavingsAccount::SavingsAccount(int id, string ownerName, int balance)
    : Account(id, ownerName, balance), withdrawalCount(0) {
  if (balance < minimumBalance) {
    throw invalid_argument(
        "Error: Savings account balance must be at least 100");
  }
};

void SavingsAccount::withdraw(int amount) {
  // Check number of withdrawals
  if (withdrawalCount >= withdrawalLimit) {
    cout << "You exceded withdrawal limit" << endl;
    return;
  }

  // Check current balance
  if (getBalance() - amount <= minimumBalance) {
    cout << "You can not go below minimum balance" << endl;
    return;
  }

  // Call withdraw from base class
  Account::withdraw(amount);

  // Increase withdrawal count, after successfull transaction
  withdrawalCount++;
}