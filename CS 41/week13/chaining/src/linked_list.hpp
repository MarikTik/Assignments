#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

namespace ds{
     template<typename T>
     class linked_list{
     public:

          linked_list() = default;
          linked_list(linked_list &&other) : _head(other._head), _tail(other._tail)
          {
               other._head = other._tail = nullptr;
          }
          linked_list &operator = (linked_list &&other){
               _head = other._head, _tail = other._tail;
               other._head = other._tail = nullptr;
          }

          /// @brief inserts a new element at the end of the list
          /// @tparam Arg the type of the value to be inserted
          /// @param value the value to be inserted
          /// @return void
          template<typename Arg>
          void push_back(Arg &&value){
               auto *node = new dl_node<T>(std::forward<Arg>(value));
               if (not _head) {
                    _head = node;
               }
               else if (not _tail) {
                    _tail = node;
                    _tail->attach_previous(_head);
               }
               else{
                    _tail->attach_next(node);
                    _tail = node;
               }
          }   

          /// @brief inserts a new element at the beginning of the list
          /// @tparam Arg the type of the value to be inserted
          /// @param value the value to be inserted
          /// @return void
          template<typename Arg>
          void push_front(Arg &&value){
               auto *node = new dl_node<T>(std::forward<Arg>(value));
               if (not _head){
                    _head = node;
               }
               else if (not _tail){
                    _tail = _head;
                    _head = node;
                    _head->attach_next(_tail);
               }
               else{
                    _head->attach_previous(node);
                    _head = node;
               }
          }

          /// @brief removes the first n elements from an array that satisfy a predicate
          /// @tparam Predicate the type of the predicate to be used
          /// @param predicate the predicate to be used to remove elements
          /// @param n the number of elements to remove, if set to 0, all elements that satisfy the predicate will be removed
          /// @return void
          template<typename Predicate>
          void remove(Predicate predicate, size_t n = 1){
               if (n == 0) n = -1;

               for (auto *ptr = _head; ptr; ptr = ptr->next){
                    if (std::invoke(predicate, ptr->data)){
                         auto *next = ptr->next;
                         if (ptr == _head){
                              delete _head;
                              _head = next;
                         }
                         else{
                              auto *previous = ptr->previous;
                              previous->attach_next(next);
                              delete ptr;
                         }
                         if (--n == 0) return;
                    }
               }
          }

          bool empty() const{
               return _head;
          }

          void clear(){
               for (auto *previous = _head; previous; previous = previous->next) 
                    delete previous;
               _head = _tail = nullptr;
          }

          class iterator {
               public:
                    using iterator_category = std::bidirectional_iterator_tag;
                    using difference_type = std::ptrdiff_t;
                    using value_type = T;
                    using pointer = value_type *;
                    using reference = value_type &;

                    iterator() = default;
                    iterator(dl_node<T> *head) : current(head) {}
                    reference& operator *() const {return current->data;}
                    iterator& operator ++() {current = current->next; return *this;}
                    iterator operator ++(int) {iterator tmp = *this; current = current->next; return tmp;}
                    iterator& operator --() {current = current->previous; return *this;}
                    iterator operator --(int) {iterator tmp = *this; current = current->previous; return tmp;}
                    bool operator ==(const iterator &other) const {return current == other.current;}
                    bool operator !=(const iterator &other) const {return current != other.current;}

               private:
                   dl_node<T> *current = nullptr;
          };

          iterator begin() const { return iterator(_head); }
          iterator end() const { return iterator(nullptr); }
          ~linked_list(){ clear(); }

     private:
          dl_node<T> *_head = nullptr, *_tail = nullptr;
     };
}
#endif