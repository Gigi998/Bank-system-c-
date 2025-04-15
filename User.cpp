#include "./include/User.h"

#include <algorithm>
#include <fstream>
#include <sstream>

#include "./include/CheckingAccount.h"
#include "./include/SavingsAccount.h"

User::User(int id, string name) {
  this->id = id;
  this->name = name;

  loadAccounts();
};

User::~User() {
  cout << "User destruct" << endl;

  saveAccounts();

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

void User::saveAccounts() {
  ofstream Accounts("accounts-" + getName() + ".txt");
  for (Account* accountPtr : accounts) {
    accountPtr->save(Accounts);
  }

  Accounts.close();
}

void User::loadAccounts() {
  string accountsText;
  ifstream Accounts("accounts-" + getName() + ".txt");

  while (getline(Accounts, accountsText)) {
    // Get balance line
    if (accountsText.rfind("Balance", 0) == 0) {
      size_t start = accountsText.find(":") + 1;

      std::string balStr = accountsText.substr(start);

      double balance = stod(balStr);

      addCheckingAccount(balance);

      getline(Accounts, accountsText);
      if (accountsText == "Transactions") {
        while (getline(Accounts, accountsText)) {
          // Find "Amount:"
          size_t amountPos = accountsText.find("Amount:");
          size_t amountEnd = accountsText.find(",", amountPos);
          std::string amountStr =
              accountsText.substr(amountPos + 7, amountEnd - (amountPos + 7));
          double amount = std::stod(amountStr);

          size_t descStart = amountEnd + 1;
          size_t finalPos = accountsText.find("Final Balance:");
          std::string desc =
              accountsText.substr(descStart, finalPos - descStart);
          desc.erase(0, desc.find_first_not_of(" ,"));
          desc.erase(desc.find_last_not_of(" ,") + 1);
          string description = desc;

          // Extract final balance
          std::string finalStr = accountsText.substr(finalPos + 14);
          finalStr.erase(0, finalStr.find_first_not_of(" "));
          double finalBalance = std::stod(finalStr);
        }
      }
    }
  }

  Accounts.close();
}
