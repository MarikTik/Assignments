#include <iostream>
#include <string>
#include <vector>
#include <sstream>


// I left this function to underscore the fact that I understand the algorithm, but it's nothing more than reinventing the wheel.

bool is_numeric(const std::string& string){
     if (string.empty()) 
          return false;

     bool last_character_is_digit = true; // setting as true because ".[digits]" is a valid number

     for(char character : string){
          bool current_character_is_digit = std::isdigit(character); //std::isdigit() can be substituted with ('0' <= character and character <= '9')
          
          if (character == '.'){
               if (not last_character_is_digit)
                    return false;
          }
          else if (not current_character_is_digit )
               return false;

          last_character_is_digit = current_character_is_digit;
     }
     return true;
}

int main(){
     std::string sentence, token;
     std::getline(std::cin, sentence);
     std::vector<std::string> words;
     std::istringstream iss(sentence);
     const char delimiter = ' ';
     
     while (std::getline(iss, token, delimiter))  // I could iterate over a string in search of spaces but it seems redundant.
          words.push_back(token);
      
     for (const std::string& word : words){
          char *conversion_failed_flag;
          double value = std::strtod(word.c_str(), &conversion_failed_flag);

          if (*conversion_failed_flag)
               std::cout << word << std::endl;
          else
               std::cout << value * 2 << std::endl;
     }
}
