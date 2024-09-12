#ifndef DL_NODE_HPP
#define DL_NODE_HPP


template<typename T>
struct dl_node{
     public:
          template<typename TForward>
          dl_node(TForward &&val) : data(std::forward<TForward>(val))
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
          dl_node<T> *previous;
          dl_node<T> *next;
};

#endif