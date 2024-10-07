#ifndef BUFFER_HPP
#define BUFFER_HPP

namespace ds::_utils{
     /// @brief base buffer class that provides a common interface for all types of ordered lists
     /// @tparam T the type of the elements to be stored in the list 
     /// @tparam Allocator the type of the allocator to be used for memory management
     template<typename T, typename Allocator = std::allocator<T>>
     class buffer{
          public:
               buffer() : _buffer(_allocator.allocate(_default_capacity)), _capacity(_default_capacity) {}
               buffer(size_t capacity) : _buffer(_allocator.allocate(capacity)), _capacity(capacity) {}
               buffer(buffer &&other) : _buffer(other._buffer), _capacity(other._capacity), _size(other._size) {
                    other._buffer = nullptr, other._capacity = 0, other._size = 0;
               }
               buffer &operator =(buffer &&other){
                    if (this == &other) return *this;
                    delete[] _buffer;
                    _buffer = other._buffer, _size = other._size, _capacity = other._capacity;
                    other._buffer = nullptr, other._size = 0, other._capacity = 0;
                    return *this;
               }

               /// @brief returns the available capacity of the list
               /// @return size_t
               inline size_t capacity() const {return _capacity;}

               /// @brief returns the currrent number of elements in the list
               /// @return size_t
               inline size_t size() const {return _size;}

               /// @brief reserves a new capacity for the list, if the new capacity is less than the current capacity, the function does nothing
               /// @param new_capacity the new capacity to be reserved
               /// @return void
               void reserve(size_t new_capacity){
                    if (new_capacity <= _capacity) return;

                    T *new_buffer = _allocator.allocate(new_capacity);
                    if (_buffer){
                         std::move(_buffer, _buffer + _size, new_buffer);
                         _allocator.deallocate(_buffer, _capacity);
                    }
                    _buffer = new_buffer;
                    _capacity = new_capacity;
               }
               /// @brief shrinks the capacity of the list to the current size of the list
               /// @return void
               void shrink_to_fit(){
                    if (_size == _capacity or not _size) return;
                    T *new_buffer = _allocator.allocate(_size);
                    std::move(_buffer, _buffer + _size, new_buffer);
                    _allocator.deallocate(_buffer, _capacity);
                    _buffer = new_buffer;
                    _capacity = _size;
               }

               /// @brief clears the list and deallocates the memory
               /// @return void
               void clear() { 
                    delete[] _buffer, _capacity = _size = 0, _buffer = nullptr;
               }
               ~buffer() {
                    clear();
               }
          protected:
               T *_buffer = nullptr;
               size_t _capacity, _size = 0; 
               Allocator _allocator;
          
          private:
               constexpr static size_t _default_capacity = 8;
     };
}

#endif