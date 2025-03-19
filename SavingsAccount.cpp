#include "./include/SavingsAccount.h"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

using namespace std;

SavingsAccount::SavingsAccount(int id, string ownerName, double balance)
    : Account(id, ownerName, balance), withdrawalCount(0) {
  if (balance < minimumBalance) {
    throw invalid_argument(
        "Error: Savings account balance must be at least 100");
  };
  stopThread = false;
  // Initialize thread, it takes pointer function and instance object
  interestThread = thread(&SavingsAccount::addInterests, this);
};

SavingsAccount::~SavingsAccount() {
  // Stop the thread running condition
  stopThread = true;
  // Ensures that thread is finished before destructor call
  if (interestThread.joinable()) {
    interestThread.join();
  }
}

void SavingsAccount::withdraw(double amount) {
  // Check number of withdrawals
  if (withdrawalCount >= withdrawalLimit) {
    cout << "You exceded withdrawal limit" << endl;
    addTransaction(0, "Failed, withdraw limit exceded", getBalance());
    return;
  }

  // Check current balance
  if (getBalance() - amount <= minimumBalance) {
    cout << "You can not go below minimum balance" << endl;
    addTransaction(0, "Failed, minimum balance", getBalance());
    return;
  }

  // Call withdraw from base class
  Account::withdraw(amount);

  // Increase withdrawal count, after successfull transaction
  withdrawalCount++;
}

// PRIVATE
void SavingsAccount::addInterests() {
  while (!stopThread) {
    // Add interest every 5 seconds, simulates monthly/yearly yield
    this_thread::sleep_for(chrono::seconds(5));

    balance += balance * interest;
    addTransaction(balance * interest, "Interests", getBalance());
  }
}