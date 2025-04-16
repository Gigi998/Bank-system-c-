#include "./include/User.h"

#include <algorithm>
#include <fstream>
#include <sstream>

#include "./include/CheckingAccount.h"
#include "./include/SavingsAccount.h"

// Trim helper
std::string trim(const std::string& str) {
  size_t first = str.find_first_not_of(" \t\r\n");
  size_t last = str.find_last_not_of(" \t\r\n");
  return (first == std::string::npos) ? ""
                                      : str.substr(first, (last - first + 1));
}

// Parse one transaction line
Account::TransactionType parseTransactionLine(const std::string& line) {
  Account::TransactionType t;
  size_t amountPos = line.find("Amount:");
  size_t amountEnd = line.find(",", amountPos);
  string amountStr = line.substr(amountPos + 7, amountEnd - (amountPos + 7));
  t.amount = std::stod(trim(amountStr));

  size_t finalPos = line.find("Final Balance:");
  string desc = line.substr(amountEnd + 1, finalPos - (amountEnd + 1));
  t.type = trim(desc);

  std::string finalStr = line.substr(finalPos + 14);
  t.finalBalance = std::stod(trim(finalStr));

  return t;
}

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
    Accounts << "Type: " << accountPtr->getType() << endl;

    accountPtr->save(Accounts);
  }

  Accounts.close();
}

void User::loadAccounts() {
  string accountsText;
  ifstream Accounts("accounts-" + getName() + ".txt");

  while (getline(Accounts, accountsText)) {
    if (accountsText.rfind("Type", 0) == 0) {
      string typeStr = trim(accountsText.substr(5));

      Account* account = nullptr;

      getline(Accounts, accountsText);

      double balance =
          stod(trim(accountsText.substr(accountsText.find(":") + 1)));

      if (typeStr == "savings") {
        account = new SavingsAccount(accounts.size() + 1, name, balance);
      } else if (typeStr == "checking") {
        account = new CheckingAccount(accounts.size() + 1, name, balance);
      }

      accounts.push_back(account);

      getline(Accounts, accountsText);

      while (getline(Accounts, accountsText) && !accountsText.empty() &&
             accountsText.rfind("Type:", 0) != 0) {
        Account::TransactionType t = parseTransactionLine(accountsText);
        account->addTransaction(t.amount, t.type, t.finalBalance);
      }

      // If we just read a new Type line, rewind the loop back to it
      if (accountsText.rfind("Type:", 0) == 0) {
        Accounts.seekg(-static_cast<int>(accountsText.size()) - 1,
                       std::ios_base::cur);
      }
    }
  }

  Accounts.close();
}
