#include <ostream>
#include <iostream>
#include <functional>
#include <string>

template<typename T>
struct node {
     node(T value) : data(value)
     {      
     }
     T data;
     node<T> *next = nullptr;
     node<T> *previous = nullptr;
};

template<typename T, typename U>
class sorted_node_order{
     public:
          template<typename Comparator>
          void insert(T _t_head_value, U _u_head_value, Comparator comparator){
               node<T> *t_node = new node<T>(_t_head_value);
               node<U> *u_node = new node<U>(_u_head_value);

               if (not _t_head)
               {
                    _t_head = t_node;
                    _u_head = u_node;
                    return;
               }
               node<T> *t_current = _t_head;
               node<T> *t_previous = nullptr;

               node<U> *u_current = _u_head;
               node<U> *u_previous = nullptr;

               while (t_current and comparator(t_current->data, _t_head_value)){
                    t_previous = t_current;
                    t_current = t_current->next;

                    u_previous = u_current;
                    u_current = u_current->next;
               }
     
               if (not t_previous) // the comparator returned false immediately, hence swap head with new node
               {
                    t_node->next = _t_head;
                    _t_head->previous = t_node;
                    _t_head = t_node;

                    u_node->next = _u_head;
                    _u_head->previous = u_node;
                    _u_head = u_node;
               }
               else if (t_current){ // the comparator returned false hence there is a continuation of the list to attach
                    t_previous->next = t_node;
                    t_node->previous = t_previous;
                    t_node->next = t_current;
                    t_current->previous = t_node;

                    u_previous->next = u_node;
                    u_node->previous = u_previous;
                    u_node->next = u_current;
                    u_current->previous = u_node;
               }
               else{ // end of list reached, so the new node is the last one
                    t_previous->next = t_node;
                    t_node->previous = t_previous;

                    u_previous->next = u_node;
                    u_node->previous = u_previous;
               }
          }

          friend std::ostream & operator << (std::ostream &os, const sorted_node_order<T, U> &order){
               node<T> *t_ptr = order._t_head;
               node<U> *u_ptr = order._u_head;

               if (not t_ptr)
                    return os;

               os << t_ptr->data << " - " << u_ptr->data;
               t_ptr = t_ptr->next;
               u_ptr = u_ptr->next;
               while (t_ptr){
                    os << ", " << t_ptr->data << " - " << u_ptr->data;
                    t_ptr = t_ptr->next;
                    u_ptr = u_ptr->next;
               }
               return os;
          }
          void clear(){
               node<T> *t_current = _t_head;
               node<T> *t_next = nullptr;
               while (t_current){
                    t_next = t_current->next;
                    delete t_current;
                    t_current = t_next;
               }
               node<U> *u_current = _u_head;
               node<U> *u_next = nullptr;
               while (u_current){
                    u_next = u_current->next;
                    delete u_current;
                    u_current = u_next;
               }
          }
          ~sorted_node_order(){
               clear();
          }
     private:
          node<T>* _t_head = nullptr;
          node<U>* _u_head = nullptr;
};


template<typename T, typename U>
class sorted_list{

     template<typename Y>
     using comparator_t = std::function<bool(Y, Y)>;

     public:
          sorted_list(comparator_t<T> t_comparator, comparator_t<U> u_comparator) 
               : _t_comparator(t_comparator), _u_comparator(u_comparator)
          {
          }
          sorted_list() = default;

          void insert(T first_value, U second_value){
               _t_order.insert(first_value, second_value, _t_comparator);
               _u_order.insert(second_value, first_value, _u_comparator);
          }

          void print_first_order(std::ostream &os = std::cout) const{
               os << _t_order;
          }
          void print_second_order(std::ostream &os = std::cout) const{
               os << _u_order;
          }
     private:
          sorted_node_order<T, U> _t_order;
          sorted_node_order<U, T> _u_order;

          comparator_t<T> _t_comparator;
          comparator_t<U> _u_comparator;
};


class application{
     public:
          void run(size_t persons_n){
               for (size_t i = 0; i < persons_n; i++){
                    std::string name;
                    double weight;
                    std::cin >> name >> weight;
                    _list.insert(name, weight);
               }
               std::cout << "Names & weights sorted(ascending) by name. : ";
               _list.print_first_order();

               std::cout << "\nNames & weights sorted(ascending) by weight. : ";
               _list.print_second_order();
               std::cout << std::endl;
          }
     private:
          sorted_list<std::string, double> _list{
               std::less<const std::string &>{},
               std::less<double >{}
          };
};
 
int main(){
     application app;
     app.run(15);
}