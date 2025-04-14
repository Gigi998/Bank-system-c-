#include "./include/User.h"

#include <algorithm>

#include "./include/CheckingAccount.h"
#include "./include/SavingsAccount.h"

User::User(int id, string name) {
  this->id = id;
  this->name = name;
};

User::~User() {
  cout << "User destruct" << endl;
  for (auto acc : accounts) {
    // Deleting one by one, becaouse it is separetely allocated object
    delete acc;
  }

  // Delete all pointers from vector, doesn't delete actual
  // object, so we need to manualy delete object first
  accounts.clear();
}

void User::getDetails() {
  cout << "User id: " << id << ", name is: " << name << endl;

  cout << "ACCOUNTS" << endl;

  cout << "--------------" << endl;

  for (const auto& acc : accounts) {
    acc->getDetails();
  }
}

void User::addCheckingAccount(int balance) {
  // Manualy allocate memory, to persist after function is finished
  accounts.push_back(new CheckingAccount(accounts.size() + 1, name, balance));
  cout << "Account added\n";
}

void User::addSavingsAccount(int balance) {
  // Manualy allocate memory, to persist after function is finished
  accounts.push_back(new SavingsAccount(accounts.size() + 1, name, balance));
  cout << "Account added\n";
}

Account* User::findAccount(int accountId) {
  for (Account* account : accounts) {
    if (account->getId() == accountId) {
      return account;
    }
  }

  return nullptr;
}

void User::removeAccount(int accountId) {
  Account* accountPtr = findAccount(accountId);

  if (accountPtr == nullptr) {
    cout << "Account not found" << endl;
  } else {
    delete accountPtr;
    accounts.erase(remove(accounts.begin(), accounts.end(), accountPtr),
                   accounts.end());
  }
}

void User::deposit(int accountId, int amount) {
  Account* accountPtr = findAccount(accountId);

  if (!accountPtr) {
    cout << "Account not found" << endl;
    return;
  }

  accountPtr->deposit(amount);
}

void User::withdraw(int accountId, int amount) {
  Account* accountPtr = findAccount(accountId);

  if (!accountPtr) {
    cout << "Account not found" << endl;
    return;
  }

  accountPtr->withdraw(amount);
}

string User::getName() { return name; }
