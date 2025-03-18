#include <iostream>
#include <string>

using namespace std;

class Account {
 private:
  struct TransactionType {
    int amount;
    string type;
    int finalBalance;
  };

  int id;
  int balance;
  string ownerName;
  int transactionsCount;
  TransactionType* transactions;

  void addTransaction(int amount, string type, int finalBalance);

 public:
  Account(int id, string ownerName, int balance);

  ~Account();

  Account(const Account& original);

  void deposit(int amount);

  void withdraw(int amount);

  void getDetails();

  int getBalance();
};