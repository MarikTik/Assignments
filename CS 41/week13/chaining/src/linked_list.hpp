#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP
#include "dl_node.hpp"
#include <limits>
#include <type_traits>
#include <algorithm>

namespace ds{
     template<
          typename T,
          typename Allocator = std::allocator<dl_node<T>>
     >
     class linked_list{
          using allocator_t = Allocator;
          using node_t = dl_node<T>;
          using node_allocator_t = typename std::allocator_traits<Allocator>::template rebind_alloc<node_t>;
          using node_allocator_traits_t = std::allocator_traits<node_allocator_t>;

          template<typename> class basic_iterator;
     public:

          using iterator = basic_iterator<T>;
          using const_iterator = basic_iterator<const T>;
          /// @brief Constructs an empty linked list.
          linked_list() = default;

          /// @brief Constructs a linked list as a copy of another list.
          /// @param other The linked list to copy from.
          linked_list(const linked_list &other) 
               : _allocator(other._allocator),
                 _node_allocator(other._node_allocator)
          {
               insert_back(other.begin(), other.end());
          }

          /// @brief Assigns the contents of another linked list to this one.
          /// @param other The linked list to copy from.
          /// @return Reference to the current object.
          linked_list &operator =(const linked_list &other){
               if (this != &other)
               {
                    clear();
                    _allocator = other._allocator;
                    _node_allocator = other._node_allocator;
                    insert_back(other.begin(), other.end());
               }
               return *this;
          }

          /// @brief Constructs a linked list by moving the contents of another list.
          /// @param other The linked list to move from.
          linked_list(linked_list &&other) noexcept
               : _head(other._head), _tail(other._tail),
               _allocator(std::move(other._allocator)),
               _node_allocator(std::move(other._node_allocator))
          {
               other._head = other._tail = nullptr;
          }

          /// @brief Moves the contents of another linked list into this one.
          /// @param other The linked list to move from.
          /// @return Reference to the current object.
          linked_list &operator = (linked_list &&other) noexcept{
               if (this != &other) {
                    std::swap(_head, other._head);
                    std::swap(_tail, other._tail);
                    std::swap(_allocator, other._allocator);
                    std::swap(_node_allocator, other._node_allocator);
               }
               return *this;
          }

          /// @brief Inserts a new element at the end of the list.
          /// @tparam Args The types of the arguments to construct the element.
          /// @param args The arguments to forward to the element's constructor.
          template<typename... Args>
          void emplace_back(Args &&...args){
               auto *node = _node_allocator.allocate(1);
               node_allocator_traits_t::construct(_node_allocator, node, std::forward<Args>(args)...);

               if (not _head) {
                    _head = _tail = node;
               }
               else{
                    _tail->attach_next(node);
                    _tail = node;
               }
          }

          /// @brief Inserts a new element at the beginning of the list.
          /// @tparam Args The types of the arguments to construct the element.
          /// @param args The arguments to forward to the element's constructor.
          template<typename... Args>
          void emplace_front(Args &&...args){
               auto *node = _node_allocator.allocate(1);
               node_allocator_traits_t::construct(_node_allocator, node, std::forward<Args>(args)...);

               if (not _head){
                    _head = _tail = node;
               }
               else{
                    _head->attach_previous(node);
                    _head = node;
               }
          }

          /// @brief Inserts a new element at the end of the list.
          /// @tparam Arg The type of the value to be inserted.
          /// @param value The value to be inserted.
          template<typename Arg>
          void push_back(Arg &&value){
               emplace_back(std::forward<Arg>(value));
          }   

          /// @brief Inserts a new element at the beginning of the list.
          /// @tparam Arg The type of the value to be inserted.
          /// @param value The value to be inserted.
          template<typename Arg>
          void push_front(Arg &&value){
               emplace_front(std::forward<Arg>(value));
          }

          /// @brief Inserts a range of elements into the back of the list.
          /// @tparam InputIt The type of the input iterator.
          /// @param begin Iterator to the beginning of the range.
          /// @param end Iterator to the end of the range.
          template<typename InputIt>
          void insert_front(InputIt begin, InputIt end){
               for (auto it = begin; it != end; ++it)
                    push_back(*it);
          }

          /// @brief Inserts a range of elements into the front of the list.
          /// @tparam InputIt The type of the input iterator.
          /// @param begin Iterator to the beginning of the range.
          /// @param end Iterator to the end of the range.
          template<typename InputIt>
          void insert_back(InputIt begin, InputIt end){
               for (auto it = begin; it != end; ++it)
                    push_front(*it);
          }
          
          /// @brief Returns the number of elements in the list.
          /// @note This function has linear complexity.
          /// @return The size of the list.
          size_t size() const {
               size_t count = 0;
               for (auto* ptr = _head; ptr != nullptr; ptr = ptr->next) ++count;
               return count;
          }

          /// @brief Checks if the list is empty.
          /// @return True if the list is empty, false otherwise. 
          bool empty() const{
               return not _head;
          }

          /// @brief Clears the contents of the list.
          void clear(){
               auto* ptr = _head;
               _head = _tail = nullptr;

               while (ptr) {
                   auto* next = ptr->next;
                   node_allocator_traits_t::destroy(_node_allocator, ptr);
                   _node_allocator.deallocate(ptr, 1);
                   ptr = next;
               }
          }

          /// @brief Erases an element from the list by the specified iterator.
          /// @param it The iterator pointing to the element to erase.
          /// @return Iterator to the next element in the list.
          iterator erase(iterator it) {
               if (it == end()) return end();

               dl_node<T>* node = it._ptr;
               dl_node<T>* next = node->next;
               dl_node<T>* previous = node->previous;

               if (previous) previous->next = next;
               else _head = next;

               if (next) next->previous = previous;
               else _tail = previous;

               node_allocator_traits_t::destroy(_node_allocator, node);
               _node_allocator.deallocate(node, 1);

               return iterator(next);
          }    

          /// @brief Removes elements from the specified range that satisfy a predicate.
          /// @tparam Predicate the type of the predicate function.
          /// @param predicate the predicate function.
          /// @param begin the iterator to the beginning of the range.
          /// @param end the iterator to the end of the range.
          /// @return iterator to the next element after the last removed element.
          template<typename Predicate>
          iterator remove_if(Predicate predicate, iterator begin, iterator end){
               auto it = std::find_if(begin, end, predicate);
               return erase(it);
          }    

          /// @brief Removes elementsfrom the list that satisfy a predicate.
          /// @tparam Predicate the type of the predicate function.
          /// @param predicate the predicate function.
          /// @return the iterator to the next element after the last removed element.
          template<typename Predicate>
          iterator remove_if(Predicate predicate){
               return remove_if(predicate, begin(), end());
          }

          /// @brief Returns an iterator to the beginning of the list.
          iterator begin() { return iterator(_head); }

          /// @brief Returns an iterator to the end of the list.
          iterator end() { return iterator(nullptr); }

          /// @brief Returns a const iterator to the beginning of the list.
          const_iterator cbegin() const { return const_iterator(_head); }

          /// @brief Returns a const iterator to the end of the list. 
          const_iterator cend() const { return const_iterator(nullptr); }

          /// @brief Returns a const iterator to the beginning of the list.
          /// @note This function is provided for compatibility with the standard library. Use cbegin() instead.
          const_iterator begin() const { return const_iterator(_head); }

          /// @brief Returns a const iterator to the end of the list.
          /// @note This function is provided for compatibility with the standard library. Use cend() instead.
          const_iterator end() const { return const_iterator(nullptr); }

          /// @brief Returns a reference to the first element in the list.
          /// @return T&
          T& front() const { return _head->data; }
          
          /// @brief Returns a const reference to the first element in the list.
          //const T& front() const { return _head->data; }

          /// @brief Returns a reference to the last element in the list.
          /// @return 
          T& back() const { return _tail->data; }

          /// @brief Returns a const reference to the last element in the list.
          /// @return
          //const T& back() const { return _tail->data; }

          /// @brief Destructor that clears the contents of the list.
          ~linked_list(){ 
               clear();
          }

     private:
          dl_node<T> *_head = nullptr, *_tail = nullptr;
          allocator_t _allocator;
          node_allocator_t _node_allocator;

          template<typename U>
          class basic_iterator {
          public:
               using iterator_category = std::bidirectional_iterator_tag;
               using difference_type = std::ptrdiff_t;
               using value_type = U;
               using pointer = value_type*;
               using reference = value_type&;


               basic_iterator() = default;
               explicit basic_iterator( dl_node<T> *ptr) : _ptr(ptr) {}
               reference operator*() const { return _ptr->data; }
               pointer operator->() const { return &(_ptr->data); }
               basic_iterator& operator++() {_ptr = _ptr->next; return *this; }
               basic_iterator operator++(int) {basic_iterator tmp = *this; ++(*this); return tmp; }
               basic_iterator& operator--() {_ptr = _ptr->previous; return *this; }
               basic_iterator operator--(int) {basic_iterator tmp = *this; --(*this); return tmp; }
               bool operator==(const basic_iterator& other) const { return _ptr == other._ptr; }
               bool operator!=(const basic_iterator& other) const { return _ptr != other._ptr; }

          private:
               dl_node<T> *_ptr = nullptr;    
               friend class linked_list;
          };
     };
}
#endif