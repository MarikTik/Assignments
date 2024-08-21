#include <iostream>
#include <stdexcept>

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
                    throw std::underflow_error("attempted to pop an element from stack, but it is empty");

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


//sample program
int main(){
     stack<int> stk;
     for (int i = 0; i < 10; i ++)
          stk.push(i);

     while(!stk.is_empty())
          std::cout << stk.pop() << std::endl;
}