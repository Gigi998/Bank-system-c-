#include <iostream>
#include <stdexcept>

#include "./include/SavingsAccount.h"

using namespace std;

int main() {
  try {
    SavingsAccount acc1(1, "Luigi", 500);
    acc1.withdraw(40);
    acc1.withdraw(40);
    acc1.deposit(200);
    acc1.withdraw(40);
    acc1.withdraw(40);
    acc1.getDetails();
  } catch (const invalid_argument& e) {
    cerr << e.what() << endl;
  };

  return 0;
}