#ifndef ORDERED_BUFFER_HPP
#define ORDERED_BUFFER_HPP

namespace ds::_utils{
     /// @brief base buffer class that provides a common interface for all types of ordered lists
     /// @tparam T the type of the elements to be stored in the list
     template<typename T>
     class ordered_buffer{
          public:
               ordered_buffer() : _buffer(new T[_default_capacity]), _capacity(_default_capacity) {}
               ordered_buffer(size_t capacity) : _buffer(new T[capacity]), _capacity(capacity) {}
               ordered_buffer(ordered_buffer &&other) : _buffer(other._buffer), _size(other._size), _capacity(other._capacity) {}
               ordered_buffer &operator =(ordered_buffer &&other){
                    if (this == &other) return *this;
                    delete[] _buffer;
                    _buffer = other._buffer, _size = other._size, _capacity = other._capacity;
                    other._buffer = nullptr, other._size = 0, other._capacity = 0;
                    return *this;
               }

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
                    T *new_buffer = new T[new_capacity];
                    std::move(_buffer, _buffer + _size, new_buffer);
                    delete[] _buffer;
                    _buffer = new_buffer;
                    _capacity = new_capacity;
               }

               iterator begin() {return iterator(_buffer);}
               iterator end() {return iterator(_buffer + _size);}

               void clear() { delete[] _buffer, _capacity = _size = 0;}
               ~ordered_buffer() { clear(); }
          protected:
               T *_buffer = nullptr;
               size_t _capacity, _size = 0; 
          
          private:
               constexpr static size_t _default_capacity = 8;
     };
}

#endif