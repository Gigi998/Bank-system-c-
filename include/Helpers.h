#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>

#include "./Account.h"

using namespace std;

string trim(const std::string& str);

// Parse one transaction line
Account::TransactionType parseTransactionLine(const std::string& line);

#endif