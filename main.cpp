#include <iostream>
#include <stdexcept>

#include "./include/CheckingAccount.h"
#include "./include/SavingsAccount.h"
#include "./include/User.h"

using namespace std;

void menu() {
  cout << "\n Bank Management System \n";
  cout << "--------------------------------\n";
  cout << "1️⃣ Get details/transactions\n";
  cout << "2️⃣ Add Savings account\n";
  cout << "3 Add Checking account\n";
  cout << "4 Remove account\n";
  cout << "5 Deposit\n";
  cout << "6 Withdraw\n";
  cout << "7 Exit\n";
  cout << "--------------------------------\n";
  cout << "Choose an option: ";
}

int main() {
  User user1(1, "Luigi");

  bool isRunning = true;

  while (isRunning) {
    menu();

    int choice = 0;

    cin >> choice;

    int balance;
    int accountNumber;
    int transactionAmount;

    switch (choice) {
      case 1:
        user1.getDetails();
        break;
      case 2:
        cout << "Savings account balance: ";
        cin >> balance;
        while (SavingsAccount::minimumBalance > balance) {
          cout << "Creation failed, minimum required balance is 100" << endl;
          cout << "Savings account balance: ";
          cin >> balance;
        }
        user1.addSavingsAccount(balance);
        break;
      case 3:
        cout << "Checking account balance: ";
        cin >> balance;
        while (balance < 0) {
          cout << "Creation failed, minimum required balance is 0, can't go "
                  "below"
               << endl;
          cout << "Checking account balance: ";
          cin >> balance;
        }
        user1.addCheckingAccount(balance);
        break;
      case 4:
        cout << "Account Id: ";
        cin >> accountNumber;
        user1.removeAccount(accountNumber);
        break;
      case 5:
        cout << "Accout Id: ";
        cin >> accountNumber;
        cout << "Deposit amount:";
        cin >> transactionAmount;
        user1.deposit(accountNumber, transactionAmount);
        break;
      case 6:
        cout << "Account Id: ";
        cin >> accountNumber;
        cout << "Withdraw amount: ";
        cin >> transactionAmount;
        user1.withdraw(accountNumber, transactionAmount);
        break;
      case 7:
        cout << "Exiting" << endl;
        isRunning = false;
        break;
      default:
        break;
    }
  }

  return 0;
}