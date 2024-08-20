#include <iostream>
#include <stdexcept>
// Note that MaxSize is indeed constant here.
template <typename T, size_t MaxSize = 10>
class queue
{    
     public:
          bool is_empty() const{
               return not _count;
          }
          void enqueue(T item){
               if (_count == MaxSize)
                    throw std::overflow_error("attempted to add an element to queue, but it is full");

               _data[_back] = item;
               _back = (_back + 1) % MaxSize;
               _count ++;

          }
          T dequeue(){
               if (is_empty())
                    throw std::underflow_error("attempted to remove and element from queue, but it is empty");

               T value = _data[_front];
               _front = (_front + 1) % MaxSize;
               _count --;
               return value;
          }

     private:
          T _data[MaxSize];
          size_t _count = 0;
          size_t _front = 0;
          size_t _back = 0;
};

// sample code:
int main(){
     queue<int, 10> q;
     for(int i = 0; i < 10; i++){
          q.enqueue(i);
     }

     for (int i = 0; i < 5; i++)
          q.dequeue();
     for (int i = 0; i < 5; i++)
          q.enqueue(15);
     
     for (int i = 0; i < 10; i++)
          std::cout << q.dequeue() << std::endl;

     return 0;
}