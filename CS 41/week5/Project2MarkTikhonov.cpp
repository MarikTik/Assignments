#include <iostream>
#include <string>
#include <istream>
#include <ostream>
#include <functional>
 
template<typename T>
struct node{
     node(T value) : data(value)
     {
           
     }
     T data;
     node<T> *next = nullptr;
     node<T> *previous = nullptr;
};


struct person{
     friend std::istream &operator >> (std::istream &is, person &person);
     friend std::ostream &operator << (std::ostream &os, const person &person);

     std::string name;
     float weight;
};

std::istream &operator>>(std::istream &is, person &person)
{
     is >> person.name >> person.weight;
     return is;
}

std::ostream &operator<<(std::ostream &os, const person &person)
{
     os << person.name << " - " << person.weight;
     return os;
}


// this implementation of linked list uses doubly linked list, as required by the assignment
template<typename T>
class sorted_list{
     using comparator_t = std::function<bool(T, T)>;
     public:
          sorted_list(comparator_t comparator)
               : _comparator(comparator)
          {
          }

          bool is_empty() const{
               return not _size;
          }
          size_t size() const{
               return _size;
          }
          void insert(T value){
               node<T> *new_node = new node<T>(value);
               if (not _head)
               {
                    _head = new_node;
                    return;
               } 
               node<T> *current = _head;
               node<T> *previous = nullptr;

               while (current and _comparator(current->data, value)){
                    previous = current;
                    current = current->next;
               }
               if (not previous) // the comparator returned false immediately, hence swap head with new node
               {
                    new_node->next = _head;
                    _head->previous = new_node;
                    _head = new_node;
               }
               else if (current){ // _comparator returned false hence there is a continuation of the list to attach
                    previous->next = new_node;
                    new_node->previous = previous;
                    new_node->next = current;
                    current->previous = new_node;
               }
               else{ // end of list reached, so the new node is the last one
                    previous->next = new_node;
                    new_node->previous = previous;
               }

          }

          friend std::ostream &operator << (std::ostream& os, const sorted_list<T>& lst){
               const auto *ptr = lst._head;
               if (not ptr)
                    return os;
               os << ptr->data;
               ptr = ptr->next;
               while(ptr){
                    os << ", " << ptr->data;
                    ptr = ptr->next;
               }
               return os;
          }

          ~sorted_list(){
               auto *ptr = _head;
               while (ptr){
                    auto *next = ptr->next;
                    delete ptr;
                    ptr = next;
               }
          }
                   
     private:
          node<T> *_head = nullptr;
          comparator_t _comparator;
          size_t _size = 0;
};
 
static const auto weight_comparator = [](const person &person1, const person &person2){
     return person1.weight < person2.weight;
};

static const auto name_length_comparator = [](const person &person1, const person &person2){
     return person1.name.size() < person2.name.size();
};

template <size_t persons_n = 15>
class application{
     public:

          void run(){
               for (size_t i = 0; i < persons_n; i++){
                    person person;
                    std::cin >> person;
                    _list_sorded_by_name_length.insert(person);
                    _list_sorted_by_weights.insert(person);
               }
               std::cout << "Names & weights sorted(ascending) by name. : " << _list_sorded_by_name_length;
               std::cout << "\nNames & weights sorted(ascending) by weight. : " << _list_sorted_by_weights;
          }
     private:
          sorted_list<person> _list_sorted_by_weights{weight_comparator};
          sorted_list<person> _list_sorded_by_name_length{name_length_comparator};
};


int main(){
     application app;
     app.run();
}