%:include <iostream>

template<typename T>
struct node{
     node(T data, node<T> *next=nullptr) : data(data), next(next)
     {
     }
     T data;
     node<T> *next;
};

template<typename T>
class sorted_list{
     public:
          void insert(T value){
               auto new_node = new node<T>(value);
               if (not _head)
               {
                    _head = new_node;
                    return;
               }
               
               node<T> *current = _head;
               node<T> *previous = _head;
               
               while (current and current->data < value){
                    previous = current;
                    current = current->next;
               }
               new_node->next = current;
               if(current == _head) // if while exited immidiately
                    _head = new_node;
               
               else
                    previous->next = new_node;
               
          }

          friend std::ostream &operator << (std::ostream &os, const sorted_list<T> &list){
               auto ptr = list._head;
               if (not ptr)
                    return os;

               os << ptr->data;
               ptr = ptr->next;
               while (ptr){
                    os << "->" << ptr->data ;
                    ptr = ptr->next;
               }
               os << "\n";
               return os;
          }
          ~sorted_list(){
               auto ptr = _head;
               while (ptr){
                    auto next = ptr->next;
                    delete ptr;
                    ptr = next;
               }
          }
     private:
          node<T>* _head = nullptr;
};
 
 
 

int main(){
     long number = 0;
     sorted_list<long> list;

     while(true){
          std::cout << "enter number:\n";
          std::cin >> number;
          if (number == -1) break;

          list.insert(number);
     }
     std::cout << list;
}    
 