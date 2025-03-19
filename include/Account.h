#include <atomic>
#include <iostream>
#include <string>

using namespace std;

class Account {
 private:
  struct TransactionType {
    double amount;
    string type;
    double finalBalance;
  };

  int id;
  string ownerName;
  int transactionsCount;
  TransactionType* transactions;

 protected:
  double balance;
  void addTransaction(double amount, string type, double finalBalance);

 public:
  Account(int id, string ownerName, double balance = 0);

  ~Account();

  Account(const Account& original);

  void deposit(double amount);

  void withdraw(double amount);

  void getDetails();

  double getBalance();
};