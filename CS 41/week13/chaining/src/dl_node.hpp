#ifndef DL_NODE_HPP
#define DL_NODE_HPP

namespace ds{
     template<typename T>
     struct dl_node{
          template<typename Arg>
          dl_node(Arg &&val) : data{std::forward<Arg>(val)}
          {
          }
          void attach_next(dl_node<T> *next_node){
               if (not next_node) return;
               next_node->previous = this;
               this->next = next_node;
          }
          void attach_previous(dl_node<T> *previous_node){
               if (not previous_node) return;
               previous_node->next = this;
               this->previous = previous_node;
          }
          T data;
          dl_node<T> *previous = nullptr;
          dl_node<T> *next = nullptr;
     };
}
#endif