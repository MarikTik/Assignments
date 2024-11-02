#ifndef STACK_HPP
#define STACK_HPP
#include "sl_node.hpp"
#include <memory>


namespace ds{
     template<
     typename T,
     typename Allocator = std::allocator<sl_node<T>>
>
class stack{
          using allocator_t = Allocator;
          using node_t = sl_node<T>;
          using node_allocator_t = typename std::allocator_traits<Allocator>::template rebind_alloc<node_t>;
          using node_allocator_traits_t = std::allocator_traits<node_allocator_t>;

     public:
          stack() = default;
          stack(const stack&) = delete;
          stack& operator=(const stack&) = delete;


          stack(stack&& other) noexcept 
               : _top(other._top), 
                 _size(other._size), 
                 _node_allocator(std::move(other._node_allocator)) {
               other._top = nullptr;
               other._size = 0;
          }

          stack& operator=(stack&& other) noexcept {
               if (this != &other) {
                    clear();
                    std::swap(_top, other._top);
                    std::swap(_size, other._size);
                    std::swap(_node_allocator, other._node_allocator);
               }
               return *this;
          }

          template<typename ...Args>
          void emplace(Args &&...args){
               auto *node = _node_allocator.allocate(1);
               node_allocator_traits_t::construct(_node_allocator, node, std::forward<Args>(args)...);

               node->next = _top;
               _top = node;
               ++_size;
          }
         
          template<typename Item>
          void push(Item &&item){
               emplace(std::forward<Item>(item));
          }

          T pop(){
               if (empty()) throw std::underflow_error("attempted to pop an element from stack, but it is empty");

               auto value = std::move(_top->data);
               auto* old_top = _top;
               _top = _top->next;

               node_allocator_traits_t::destroy(_node_allocator, old_top);
               _node_allocator.deallocate(old_top, 1);
               --_size;

               return value;
          }
          const T& peek() const{
               if (empty()) throw std::underflow_error("attempted to peek an element from stack, but it is empty");
               return _top->data;
          }

          bool empty() const{
               return not _top;
          }

          size_t size() const{
               return _size;
          }
          
          void clear() {
               while (_top) {
                    auto* next = _top->next;
                    node_allocator_traits_t::destroy(_node_allocator, _top);
                    _node_allocator.deallocate(_top, 1);
                    _top = next;
               }
               _size = 0;
          }
          ~stack(){
               clear();
          }
     private:
          sl_node<T> *_top = nullptr;
          allocator_t _allocator;
          node_allocator_t _node_allocator;
          size_t _size = 0;
     };
}



#endif