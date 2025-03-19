#include <iostream>
#include <stdexcept>

#include "./include/SavingsAccount.h"

using namespace std;

void menu() {
  cout << "\n📚 Bank Management System 📚\n";
  cout << "--------------------------------\n";
  cout << "1️⃣ Get balance\n";
  cout << "2️⃣ Deposit\n";
  cout << "3️⃣ Get details/trasactions\n";
  cout << "4️⃣ Exit\n";
  cout << "--------------------------------\n";
  cout << "Choose an option: ";
}

int main() {
  // try {
  // Handle try catch in the controler class
  SavingsAccount acc1(1, "Luigi", 200);
  SavingsAccount acc2(2, "Blanka", 300);
  // } catch (const invalid_argument& e) {
  //   cerr << e.what() << endl;
  // };

  bool isRunning = true;

  while (isRunning) {
    menu();

    int choice = 0;

    cin >> choice;
    // cin.ignore();

    switch (choice) {
      case 1:
        cout << acc1.getBalance() << endl;
        cout << acc2.getBalance() << endl;
        break;
      case 2:
        acc1.deposit(100);
        acc2.deposit(100);
        break;
      case 3:
        acc1.getDetails();
        acc2.getDetails();
        break;
      case 4:
        cout << "Exiting" << endl;
        isRunning = false;
        break;
      default:
        break;
    }
  }

  return 0;
}