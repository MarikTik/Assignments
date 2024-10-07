#ifndef CIRCULAR_LIST_HPP
#define CIRCULAR_LIST_HPP
// #include "ordered_buffer.hpp"

// namespace ds{
//      ///@brief an ordered list that has a fixed capacity and when the list is full, the new elements are added from the beginning of the list
//      ///@tparam T type of the elements to be stored in the list
//      ///@note calling reserve will invariably lead to an increase in the capacity of the circular list
//      ///while having no way to shirk the capacity of the list to the original size
//      template<typename T>
//      class circular_list : public _utils::ordered_buffer<T>{
//           public:
//                using _utils::ordered_buffer<T>::ordered_buffer;
//                using _utils::ordered_buffer<T>::operator =;

//                /// @brief inserts a new value at the end of the list, if the list is full, restarts from the beginning
//                /// @tparam Arg the type of the value to be inserted
//                /// @param value the value to be inserted
//                /// @return void
//                template<typename Arg>
//                void insert(Arg &&value){
//                     if (this->_size < this->_capacity) this->_size ++;
//                     this->_buffer[_index] = std::forward<T>(value);
//                     this->_index = (_index + 1) % this->_capacity;
//                }
               
//           private:
//                size_t _index = 0;
//      };
// }

#endif