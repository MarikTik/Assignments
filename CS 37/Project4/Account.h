#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <string>

class Account{
     public:
          Account(std::string username, std::string status="Regular");
          ~Account();

          std::string getStatus() const;
     private:
          std::string username, status;
};

#endif