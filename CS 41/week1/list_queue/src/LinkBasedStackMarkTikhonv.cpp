#include <iostream>
#include <stdexcept>




//sample program
int main(){
     stack<int> stk;
     for (int i = 0; i < 10; i ++)
          stk.push(i);

     while(!stk.is_empty())
          std::cout << stk.pop() << std::endl;
}