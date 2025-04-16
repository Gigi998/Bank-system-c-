#include "./include/Helpers.h"

// Trim helper
string trim(const string& str) {
  size_t first = str.find_first_not_of(" \t\r\n");
  size_t last = str.find_last_not_of(" \t\r\n");
  return (first == string::npos) ? "" : str.substr(first, (last - first + 1));
}

// Parse one transaction line
Account::TransactionType parseTransactionLine(const std::string& line) {
  Account::TransactionType t;
  size_t amountPos = line.find("Amount:");
  size_t amountEnd = line.find(",", amountPos);
  // substr(start,length)
  string amountStr = line.substr(amountPos + 7, amountEnd - (amountPos + 7));
  t.amount = stod(trim(amountStr));

  size_t finalPos = line.find("Final Balance:");
  string desc = line.substr(amountEnd + 1, finalPos - (amountEnd + 3));
  t.type = trim(desc);

  string finalStr = line.substr(finalPos + 14);
  t.finalBalance = stod(trim(finalStr));

  return t;
}