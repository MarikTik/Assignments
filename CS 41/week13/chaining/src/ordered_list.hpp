#ifndef ORDERED_LIST_HPP
#define ORDERED_LIST_HPP
#include <limits>
#include "buffer.hpp"
#include "index_set.hpp"

namespace ds{
     /// @brief list that keeps the elements in the order they were added
     /// @note the list will automatically increase its capacity when the number of elements exceeds the current capacity
     /// @warning retreaval of elements throgugh the [] operator is allowed, however altering the reference in any way
     /// is strongly discouraged and will impact the integrity of the list
     /// @tparam T type of the elements to be stored in the list
     template<typename T>
     class ordered_list : public _utils::buffer<T>{
          public:
               using _utils::buffer<T>::buffer;
               using _utils::buffer<T>::operator =;

               /// @brief adds a new element to the list at the end
               /// @tparam Arg the type of the element to be added
               /// @param value the value to be added to the list
               /// @return void
               template<typename Arg>
               void push_back(Arg &&value){
                    if (this->_size == this->_capacity) this->reserve(this->_capacity * 2);
                    this->_buffer[this->_size++] = std::forward<T>(value);
               }

               // ///@brief removes the first n elements from an array that satisfy a predicate
               // ///@tparam Predicate the type of the predicate to be used
               // ///@param predicate the predicate to be used to remove elements
               // ///@param n the number of elements to remove, if set to 0, all elements that satisfy the predicate will be removed 
               // ///@return void
               // template<typename Predicate>
               // void remove(Predicate predicate, size_t n = 1){
               //      if (n == 0) n = this->_size;
                    
               //      _utils::index_set flagged_indexes{this->_capacity / _utils::index_set::word_size() + 1};

               //      for (size_t i = 0; i < this->_size and n --> 0; i++)
               //           if (std::invoke(predicate, this->_buffer[i]))
               //                flagged_indexes.set(i);     
                    
               //      size_t new_capacity = this->_capacity - flagged_indexes.size();
               //      T* new_buffer = this->_allocator.allocate(new_capacity);
               //      for (size_t i = 0, j = 0; i < this->_size; i++)
               //           if (not flagged_indexes.test(i)){
               //                new_buffer[j] = std::move(this->_buffer[i + j]);
               //                j++;
               //           }
                    
               //      this->_allocator.deallocate(this->_buffer, this->_capacity);
               //      this->_buffer = new_buffer;
               //      this->_capacity = new_capacity;
               // }

               class iterator{
                    public:
                         using iterator_category = std::random_access_iterator_tag;
                         using difference_type = std::ptrdiff_t;
                         using value_type = T;
                         using pointer = value_type *;
                         using reference = value_type &;
                         iterator() = default;
                         iterator(T* ptr) : _ptr(ptr) {}
                         reference operator * () const {return *_ptr;}
                         pointer operator -> () const {return _ptr;}
                         iterator &operator ++() {++_ptr; return *this;}
                         iterator operator ++(int) {iterator temp = *this; ++(*this); return temp;}
                         iterator &operator --() {--_ptr; return *this;}
                         iterator operator --(int) {iterator temp = *this; --(*this); return temp;}
                         iterator &operator +=(difference_type n) {_ptr += n; return *this;}
                         iterator &operator -=(difference_type n) {_ptr -= n; return *this;}
                         iterator operator +(difference_type n) const {return iterator(_ptr + n);}
                         iterator operator -(difference_type n) const {return iterator(_ptr - n);}
                         difference_type operator -(const iterator &other) const {return _ptr - other._ptr;}
                         bool operator ==(const iterator &other) const {return _ptr == other._ptr;}
                         bool operator !=(const iterator &other) const {return _ptr != other._ptr;}
                         bool operator <(const iterator &other) const {return _ptr < other._ptr;}
                         bool operator > (const iterator &other) const {return _ptr > other._ptr;}
                         bool operator <= (const iterator &other) const {return _ptr <= other._ptr;}
                         bool operator >= (const iterator &other) const {return _ptr >= other._ptr;}
                    private:
                         T* _ptr = nullptr;
               };
               /// @brief removes the element pointed by the specified iterator
               /// @param it the iterator pointing to the element to be removed
               /// @return void
               void remove(iterator it){
                    if (it == this->end()) return;
                    for (auto next = it + 1; next != this->end(); it++, next++)
                         *it = std::move(*next);
                    this->_size--;
               }

               /// @brief returns a const reference to element at the specified index
               /// @param index 
               /// @return const T&
               const T& operator[](size_t index) const{
                    if (index >= this->_size) throw std::out_of_range("index out of bounds");
                    return this->_buffer[index];
               }

               

               iterator begin() {return iterator(this->_buffer);}
               iterator end() {return iterator(this->_buffer + this->_size);}
     };
}
#endif