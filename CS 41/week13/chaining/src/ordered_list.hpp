#ifndef ORDERED_LIST_HPP
#define ORDERED_LIST_HPP
#include "ordered_buffer.hpp"

namespace ds{
     /// @brief list that keeps the elements in the order they were added
     /// @tparam T type of the elements to be stored in the list
     template<typename T>
     class ordered_list : public _utils::ordered_buffer<T>{
          public:
               using _utils::ordered_buffer<T>::ordered_buffer;
               using _utils::ordered_buffer<T>::operator =;

               /// @brief adds a new element to the list at the end
               /// @tparam Arg the type of the element to be added
               /// @param value the value to be added to the list
               /// @return void
               template<typename Arg>
               void push_back(Arg &&value){
                    if (this->_size == this->_capacity) this->reserve(this->_capacity * 2);
                    this->_buffer[this->_size++] = std::forward<T>(value);
               }

               ///@brief removes the first n elements from an array that satisfy a predicate
               ///@tparam Predicate the type of the predicate to be used
               ///@param predicate the predicate to be used to remove elements
               ///@param n the number of elements to remove, if set to 0, all elements that satisfy the predicate will be removed 
               ///@return void
               template<typename Predicate>
               void remove(Predicate predicate, size_t n = 1){
                    if (n == 0) n = this->_size;
               
                    for (size_t i = 0; i < this->_size; i++){
                         if (std::invoke(predicate, this->_buffer[i])){
                              for (size_t j = i; j < this->_size - 1; j++)
                                   this->_buffer[j] = std::move(this->_buffer[j + 1]);
                              this->_size--;
                              if (not --n) break;
                         }
                    }
               }

               /// @brief removes the element pointed by the specified iterator
               /// @param it the iterator pointing to the element to be removed
               /// @return void
               void remove(typename _utils::ordered_buffer<T>::iterator it){
                    if (it == this->end()) return;
                    for (auto next = it + 1; next != this->end(); it++, next++)
                         *it = std::move(*next);
                    this->_size--;
               }
     };
}
#endif