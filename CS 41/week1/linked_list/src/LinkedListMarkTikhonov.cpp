#include <iostream>

template<typename T>
struct node{
     T data;
     node<T> *next;
};


template<typename T>
class stack{
     public:
          bool is_empty() const{
               return not _count;
          }
          void push(T item){
               auto new_node = new node<T>{.data = item};
               new_node->next = _top;
               _top = new_node;
               _count ++;
          }
          T pop(){
               if (is_empty())
                    std::underflow_error("attempted to pop an element from stack, but it is empty");

               T value = _top->data;
               auto ptr = _top;
               _top = _top->next;
               delete ptr;
               _count --;
               return value;
          }
          ~stack(){
               while(_count--)
               {
                    auto ptr = _top;
                    _top = _top->next;
                    delete ptr;
               }
          }
     private:
          node<T> *_top;
          size_t _count = 0;
};

int main(){
     stack<long> stk;
     long number = 0;
     while(number not_eq -1){
          std::cin >> number;
          stk.push(number);
     }
     stk.pop(); // removing the -1;

     while(not stk.is_empty())
          std::cout << stk.pop() << ", ";
     
     std::cout << "\b\b" << std::endl;

}