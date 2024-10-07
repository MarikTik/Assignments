#include <boost/test/unit_test.hpp>
#include "zero_init_allocator.hpp"

BOOST_AUTO_TEST_SUITE(ZERO_INIT_ALLOCATOR_TEST)

BOOST_AUTO_TEST_CASE(zero_init_allocator_allocation_test){
     ds::_utils::zero_init_allocator<int> allocator;

     // Allocate 5 integers using the custom allocator
     int* p = allocator.allocate(5);

     // Check that the allocated memory is initialized to 0
     for (size_t i = 0; i < 5; ++i) {
         BOOST_CHECK_EQUAL(p[i], 0);
     }

     allocator.deallocate(p, 5);
}

BOOST_AUTO_TEST_CASE(zero_init_allocator_allocation_larger_size_test){
     ds::_utils::zero_init_allocator<long> allocator;

     // Allocate 10 longs using the custom allocator
     long* p = allocator.allocate(10);

     // Check that the allocated memory is initialized to 0
     for (size_t i = 0; i < 10; ++i) {
         BOOST_CHECK_EQUAL(p[i], 0);
     }

     allocator.deallocate(p, 10);
}

BOOST_AUTO_TEST_CASE(zero_init_allocator_deallocation_test){
     ds::_utils::zero_init_allocator<double> allocator;

     // Allocate and deallocate memory to ensure no exceptions are thrown
     double* p = allocator.allocate(3);
     allocator.deallocate(p, 3);

     BOOST_CHECK(true); // Just checking if deallocation went fine without throwing
}

BOOST_AUTO_TEST_CASE(zero_init_allocator_bad_alloc_test){
     ds::_utils::zero_init_allocator<int> allocator;

     BOOST_CHECK_THROW(allocator.allocate(static_cast<size_t>(-1)), std::bad_alloc);
}

BOOST_AUTO_TEST_CASE(zero_init_allocator_type_test){
     ds::_utils::zero_init_allocator<char> allocator;

     // Allocate characters using the custom allocator
     char* p = allocator.allocate(4);

     // Check that the allocated memory is initialized to 0 (should be the null character)
     for (size_t i = 0; i < 4; ++i) {
         BOOST_CHECK_EQUAL(p[i], '\0');
     }

     allocator.deallocate(p, 4);
}

BOOST_AUTO_TEST_CASE(zero_init_allocator_big_allocation){
     ds::_utils::zero_init_allocator<size_t> allocator;
     size_t size = 1000000;
     size_t *arr = allocator.allocate(size);
     for (size_t i = 0; i < size; i++)
          BOOST_CHECK_EQUAL(arr[i], 0);
     allocator.deallocate(arr, size);
}

BOOST_AUTO_TEST_SUITE_END()