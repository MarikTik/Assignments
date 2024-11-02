#include <iostream>
#include <type_traits>
#include <tuple>


template <typename T>
class alignas(T) StorageFor {
 public:
  // Constructor does nothing.
  StorageFor() = default;

  // Constructs a T inside of data_.
  template <typename... Args>
  void Init(Args&&... args) {
    new (reinterpret_cast<T*>(&data_)) T(
      std::forward<Args>(args)...);
  }

  // Allow dereferencing a StorageFor into a T, like
  // a smart pointer.
  const T* get() const { return reinterpret_cast<const T*>(&data_); }
  T* get() { return reinterpret_cast<T*>(&data_); }
  const T& operator*() const { return *get(); }
  T& operator*() { return *get(); }
  const T* operator->() const { return get(); }
  T* operator->() { return get(); }
 private:
  char data_[sizeof(T)];
};
int main(){
      // Create some storage.
StorageFor<std::string> my_string;

// Separately, initialize it using std::string's constructor
// form char[N].
my_string.Init("cool type!");

// Print it out.
absl::PrintF("%s\n", *my_string);

// Destroy it. This must be done manually because StorageFor<T>
// has a trivial destructor.
using ::std::string;
my_string->~string();


}