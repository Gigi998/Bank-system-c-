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

vector<Account*>::iterator User::findAccount(int accountId) {
  auto it =
      find_if(accounts.begin(), accounts.end(),
              [&accountId](Account* acc) { return acc->getId() == accountId; });

  return it;
}

void User::removeAccount(int accountId) {
  auto it = findAccount(accountId);

  if (it != accounts.end()) {
    // Delete allocated memory(actual object), but vector still has pointer!!
    delete *it;
    // Delete the pointer from the vector
    accounts.erase(it);
    cout << "Account removed" << endl;
  } else {
    cout << "Account not found" << endl;
  }
}

string User::getName() { return name; }

void User::deposit(int accountId, int amount) {
  // Iterator pointing to a pointer account(double pointer), to access values
  // we must dereference it twice
  auto it = findAccount(accountId);

  if (it != accounts.end()) {
    // Double pointer
    (*it)->deposit(amount);
  } else {
    cout << "Account not found" << endl;
  }
}

void User::withdraw(int accountId, int amount) {
  auto it = findAccount(accountId);

  if (it != accounts.end()) {
    // Double pointer
    (*it)->withdraw(amount);
  } else {
    cout << "Account not found" << endl;
  }
}