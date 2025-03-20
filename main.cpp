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
  cout << "7 Transfer\n";
  cout << "8 Exit\n";
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
    cin.ignore();

    int balance;

    switch (choice) {
      case 1:
        user1.getDetails();
        break;
      case 2:
        cout << "Enter savings account balance: ";
        cin >> balance;
        while (SavingsAccount::minimumBalance > balance) {
          cout << "Creation failed, minimum required balance is 100" << endl;
          cout << "Enter savings account balance: ";
          cin >> balance;
        }
        user1.addSavingsAccount(balance);
        break;
      case 3:
        cout << "Enter checking account balance: ";
        cin >> balance;
        while (balance < 0) {
          cout << "Creation failed, minimum required balance is 0, can't go "
                  "negative"
               << endl;
          cout << "Enter checking account balance: ";
          cin >> balance;
        }
        user1.addCheckingAccount(balance);
        break;
      // case 4:
      //   user1.removeAccount(1);
      //   break;
      case 5:
        cout << "Exiting" << endl;
        isRunning = false;
        break;
      default:
        break;
    }
  }

  return 0;
}