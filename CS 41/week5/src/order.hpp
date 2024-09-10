#ifndef ORDER_HPP
#define ORDER_HPP
#include "node.hpp"
#include <functional>

// order that 
template<typename T, typename U>
class order{
    using comparator_t = std::function<bool(T, T)>

    public:
        order(comparator_t comparator)
            _comarator(comparator)
        {
        } 
        node<T> first;
        node<U> second;
    private:
        comparator_t _comparator;
};

#endif