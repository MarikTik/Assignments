#include <iostream>
#include <string>
#include <cstdint>
#include <iomanip>

class UserResearch;

// I could make it an old C style struct, if it is a matter of principle I could write all the private fields in the struct and add input_user_account() function. Nothing changed.
class userAccount{
    public:
        // overload to >> operator to use in with cin
        friend std::istream& operator >> (std::istream& is, userAccount& account){
            std::cin >> account.username;
            std::cin >> account.nationality;
            std::cin >> account.age;
            std::cin >> account.accountBalance;
            return is;
        }
       
    private:
        std::string username;
        std::string nationality;
        std::uint16_t age;
        double accountBalance;

      
        friend class UserResearch; //technically this is supposed to be friend conduct_and_show but for this it is preferable to have more than 1 .cpp file
};

// presents functionality to get an overview of the desired 
class UserResearch{
    public:
        UserResearch(userAccount* accounts_data, size_t accounts)
         : accounts_data(accounts_data),
           accounts(accounts)
        {
        }
        void conduct_and_show(){
            double highest_account_balance = accounts_data[0].accountBalance;
            double account_balance_sum = 0;
            size_t japanese_accounts = 0;
            size_t young_accounts = 0;

            for(size_t i=0; i < accounts; i++){
                userAccount account = accounts_data[i];

                account_balance_sum += account.accountBalance;

                if (highest_account_balance < account.accountBalance)
                    highest_account_balance = account.accountBalance;
                
                if (account.nationality == "Swedish")
                    japanese_accounts++;
                
                if (account.age < 21)
                    young_accounts++;
            }   
            std::cout << std::fixed
                      << "Q: What is the highest account balance among all users?\n"
                      <<  std::setprecision(1)
                      << "A: $" << highest_account_balance << "\n"
                      << "Q: What's the sum of account balance of all users?\n"
                      << std::setprecision(2)
                      << "A: $" << account_balance_sum << "\n"
                      << "Q: How many users come from Sweden?\n"
                      << "A: " << japanese_accounts << "\n"
                      << "Q: Do we have any user younger than 21?\n"
                      << "A: " << (young_accounts != 0 ? "Yes" : "No")
                      << std::endl;

        }
       

    private:
        userAccount* accounts_data;
        size_t accounts;
};

// Simple class to run the program and hold constants inaccessible to the rest of code
class Program{
    private:
        static constexpr char start_message[] = "Please enter information to database in the format of <username> <nationality> <age> <accountBalance>, separated each user by a newline:\n";
        static constexpr size_t max_account_number = 20;    
    public:
        void run(){
            userAccount accounts[max_account_number];
            size_t input_count = 0;

            std::cout << start_message;
            while(std::getchar() != EOF and input_count < max_account_number)
                std::cin >> accounts[input_count++];
                
            
            UserResearch research(accounts, input_count);
            research.conduct_and_show();
        }
};
int main(){
    Program project1;
    project1.run();

}

 