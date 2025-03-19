#include <iostream>
#include <stdexcept>

#include "./include/SavingsAccount.h"

using namespace std;

void menu() { cout << "Type your choice"; }

int main() {
  // try {
  // Handle try catch in the controler class
  SavingsAccount acc1(1, "Luigi", 200);
  SavingsAccount acc2(2, "Blanka", 300);
  // } catch (const invalid_argument& e) {
  //   cerr << e.what() << endl;
  // };

  while (true) {
    menu();

    int choice = 0;

    cin >> choice;
    cin.ignore();

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
      default:
        break;
    }
  }

  return 0;
}