#include "./include/SavingsAccount.h"

#include <chrono>

SavingsAccount::SavingsAccount(int id, string ownerName, double balance)
    : Account(id, ownerName, balance) {
  withdrawalCount = 0;
  stopThread = false;
  // Initialize thread, it takes pointer function and instance object
  interestThread = thread(&SavingsAccount::addInterests, this);
};

SavingsAccount::~SavingsAccount() {
  cout << "Savings destructor" << endl;
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
    addTransaction(amount, "Failed, withdraw limit exceded", getBalance());
    return;
  }

  // Check current balance
  if (getBalance() - amount <= minimumBalance) {
    cout << "You can not go below minimum balance" << endl;
    addTransaction(amount, "Failed, minimum balance", getBalance());
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

void SavingsAccount::getDetails() {
  cout << "Type: Savings Account" << endl;
  Account::getDetails();
}