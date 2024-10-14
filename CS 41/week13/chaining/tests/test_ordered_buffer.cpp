// #include <boost/test/unit_test.hpp>
// #include "buffer.hpp"

// BOOST_AUTO_TEST_SUITE(buffer_TEST)
// using namespace ds::_utils;

// BOOST_AUTO_TEST_CASE(buffer_empty_constructor_test){
//      ds::_utils::buffer<int> buffer;
//      BOOST_CHECK_EQUAL(buffer.capacity(), 8);
//      BOOST_CHECK_EQUAL(buffer.size(), 0);
     
// }
// BOOST_AUTO_TEST_CASE(buffer_capacity_initialized_test){
//      ds::_utils::buffer<int> buffer2(20);
//      BOOST_CHECK_EQUAL(buffer2.capacity(), 20);
//      BOOST_CHECK_EQUAL(buffer2.size(), 0);
// }

// BOOST_AUTO_TEST_CASE(buffer_move_constructor_test){
//      ds::_utils::buffer<int> buffer;
//      ds::_utils::buffer<int> buffer2(std::move(buffer));
//      BOOST_CHECK_EQUAL(buffer.capacity(), 0);
//      BOOST_CHECK_EQUAL(buffer.size(), 0);
//      BOOST_CHECK_EQUAL(buffer2.capacity(), 8);
//      BOOST_CHECK_EQUAL(buffer2.size(), 0);
// }

// BOOST_AUTO_TEST_CASE(buffer_multiple_reserve_test){
//      ds::_utils::buffer<int> buffer;
//      for (size_t i = 0 ; i <= 10; i++)
//           buffer.reserve(i);
   
//      BOOST_CHECK_EQUAL(buffer.capacity(), 10);
//      BOOST_CHECK_EQUAL(buffer.size(), 0);
// }

// BOOST_AUTO_TEST_CASE(ordedred_buffer_shrink_to_fit_test){
//      ds::_utils::buffer<int> buffer;
//      buffer.reserve(20);
//      buffer.shrink_to_fit();
//      BOOST_CHECK_EQUAL(buffer.capacity(), 20); // Should not change capacity since the size is 0
//      BOOST_CHECK_EQUAL(buffer.size(), 0);
// }

// BOOST_AUTO_TEST_CASE(buffer_reserve_increase_test){
//     ds::_utils::buffer<int> buffer;
//     buffer.reserve(15);
//     BOOST_CHECK_EQUAL(buffer.capacity(), 15);
//     BOOST_CHECK_EQUAL(buffer.size(), 0);
// }

// BOOST_AUTO_TEST_CASE(buffer_reserve_no_change_test){
//     ds::_utils::buffer<int> buffer(10);
//     buffer.reserve(5);  // Should not change capacity since new capacity is smaller than current capacity
//     BOOST_CHECK_EQUAL(buffer.capacity(), 10);
//     BOOST_CHECK_EQUAL(buffer.size(), 0);
// }
 
// BOOST_AUTO_TEST_CASE(buffer_move_assignment_operator_test){
//     ds::_utils::buffer<int> buffer1(20);
//     ds::_utils::buffer<int> buffer2;
//     buffer2 = std::move(buffer1);
//     BOOST_CHECK_EQUAL(buffer1.capacity(), 0);
//     BOOST_CHECK_EQUAL(buffer1.size(), 0);
//     BOOST_CHECK_EQUAL(buffer2.capacity(), 20);
//     BOOST_CHECK_EQUAL(buffer2.size(), 0);
// }

// BOOST_AUTO_TEST_CASE(buffer_clear_test){
//     ds::_utils::buffer<int> buffer(10);
//     buffer.clear();
//     BOOST_CHECK_EQUAL(buffer.capacity(), 0);
//     BOOST_CHECK_EQUAL(buffer.size(), 0);
// }

// BOOST_AUTO_TEST_CASE(buffer_reserve_after_clear_test){
//     ds::_utils::buffer<int> buffer(10);
//     buffer.clear();
//     buffer.reserve(5);
//     BOOST_CHECK_EQUAL(buffer.capacity(), 5);
//     BOOST_CHECK_EQUAL(buffer.size(), 0);
// }


// BOOST_AUTO_TEST_SUITE_END()