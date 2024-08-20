#include "Account.h"
#include <iostream>

Account::Account(std::string username, std::string status)
     : username(username), status(status)
{
}

Account::~Account()
{
     std::cout << "Account removed.\n";
}

std::string Account::getStatus() const
{
     return status;
}
