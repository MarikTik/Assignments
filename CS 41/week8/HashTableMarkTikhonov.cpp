#include <iostream>
#include <bitset>

template<typename T, size_t Size>
class hash_table{
     public:
          void insert(T value){
               const size_t original_index = _hash(value);
               size_t index = original_index;
       
               while(_positions.test(index)){
                    index = (index + 1) % Size;
                    if (index == original_index)
                         throw std::overflow_error("hash table capacity overflow");

               }

               _positions.set(index);
               _buffer[index] = value; 
          }

          int has(T value){ // returns -1 if not found, otherwise 1
               const size_t original_index = _hash(value);
               size_t index = original_index;
               
               while (true){
                    if (_buffer[index] == value) return 1; 
                    index = (index + 1) % Size;
                    if (index == original_index) return -1;
               }
          }
          
     private:
          size_t _hash(T value){
               return value % Size;
          }
          std::bitset<Size> _positions; // this helps in tracking if a value was already inserted
          T _buffer[Size];
          
};


int main(){
     
     hash_table<int, 27> table;
     
     while(true){
          std::cout << "choose: \"lookup\" or \"insertion\"\n";
          std::string choice;
          std::cin >> choice;

          if (choice == "lookup"){
               std::cout << "enter value to look for: ";
               int value;
               std::cin >> value;
               if (table.has(value) == 1)
                    std::cout << value << " found in table";
               else std::cout << value << " not found in table";
          }
          if (choice == "insertion" or choice == "insert"){
               std::cout << "enter value to insert: ";
               int value;
               std::cin >> value;
               table.insert(value);
          }
          std::cout << std::endl;
     }
}