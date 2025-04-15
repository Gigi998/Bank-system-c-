#include "./include/CheckingAccount.h"

CheckingAccount::CheckingAccount(int id, string ownerName, double balance)
    : Account(id, ownerName, balance) {};

void CheckingAccount::withdraw(double amount) {
  if (balance + overdraftLimit < amount) {
    cout << "You exceeded overdraft limit, insuficient balance" << endl;
    addTransaction(amount, "Failed, overdraft limit", getBalance());
    return;
  }

  Account::withdraw(amount);
}

void CheckingAccount::getDetails() {
  cout << "Type: Checking Account" << endl;
  Account::getDetails();
}
