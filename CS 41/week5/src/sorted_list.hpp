#ifndef SORTED_LIST_HPP
#define SORTED_LIST_HPP
#include "sorted_node_order.hpp"
#include <functional>
#include <ostream>

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

#endif