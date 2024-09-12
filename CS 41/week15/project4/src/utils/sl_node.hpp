#ifndef SL_NODE_HPP
#define SL_NODE_HPP

template<typename T>
struct sl_node{
     template<typename TForward>
     sl_node(TForward &&val) : data(std::forward<TForward>(val))
     {
     }
     void attach_next(sl_node<T> *next){
          this->next = next;
     }
     T data;
     sl_node<T> *next;
};

#endif