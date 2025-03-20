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
    delete acc;
  }
}

void User::getDetails() {
  cout << "User id: " << id << ", name is: " << name << endl;

  cout << "Accounts:" << endl;

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

// void User::removeAccount(int accountId) {
//   auto it =
//       find_if(accounts.begin(), accounts.end(),
//               [accountId](Account* acc) { return acc->getId() == accountId;
//               });

//   if (it != accounts.end()) {
//     accounts.erase(it);
//     cout << "Account removed" << endl;
//   } else {
//     cout << "Account not found" << endl;
//   }
// }

string User::getName() { return name; }