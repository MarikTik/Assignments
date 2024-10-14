#include <boost/test/unit_test.hpp>
#include "unordered_list.hpp"

#include <boost/test/unit_test.hpp>
#include <vector>
#include <numeric>
#include <algorithm>
#include "unordered_list.hpp"

BOOST_AUTO_TEST_SUITE(UNORDERED_LIST_TEST)

// Test basic functionality of the operator[]
BOOST_AUTO_TEST_CASE(unordered_list_basic_test) {
    ds::unordered_list<int, std::allocator<int>> list(10);

    // Add elements using the index operator
    list[3] = 10;
    list[5] = 20;
    list[9] = 30;

    BOOST_CHECK_EQUAL(list[3], 10);
    BOOST_CHECK_EQUAL(list[5], 20);
    BOOST_CHECK_EQUAL(list[9], 30);
}

// Test that an exception is thrown for out-of-bounds index
BOOST_AUTO_TEST_CASE(unordered_list_out_of_bounds_test) {
    ds::unordered_list<int, std::allocator<int>> list(10);

    BOOST_CHECK_THROW(list[10], std::out_of_range);  // Index beyond the capacity
}

BOOST_AUTO_TEST_CASE(unordered_list_test_size){
    ds::unordered_list<int, std::allocator<int>> list(10);
    BOOST_CHECK_EQUAL(list.size(), 0);
    list[0] = 10;
    BOOST_CHECK_EQUAL(list.size(), 1);
    list[1] = 20;
    BOOST_CHECK_EQUAL(list.size(), 2);
    list[2] = 30;
    BOOST_CHECK_EQUAL(list.size(), 3);
    std::remove(list.begin(), list.end(), 20);
}
// Test reserve functionality and reallocation
BOOST_AUTO_TEST_CASE(unordered_list_reserve_test) {
    ds::unordered_list<int, std::allocator<int>> list(5);

    list[1] = 5;
    list[3] = 10;

    list.reserve(10);  // Increase capacity

    BOOST_CHECK_EQUAL(list.capacity(), 10);
    BOOST_CHECK_EQUAL(list[1], 5);
    BOOST_CHECK_EQUAL(list[3], 10);

    list[7] = 20;
    BOOST_CHECK_EQUAL(list[7], 20);
}

// Test iterator basic functionality (increment, dereference)
BOOST_AUTO_TEST_CASE(unordered_list_iterator_basic_test) {
    ds::unordered_list<int, std::allocator<int>> list(10);

    list[1] = 5;
    list[3] = 10;
    list[7] = 20;

    auto it = list.begin();
    BOOST_CHECK_EQUAL(*it, 5);  // Check first element
    ++it;
    BOOST_CHECK_EQUAL(*it, 10);  // Check second element
    ++it;
    BOOST_CHECK_EQUAL(*it, 20);  // Check third element
}

// Test iterator comparison (equality, inequality)
BOOST_AUTO_TEST_CASE(unordered_list_iterator_comparison_test) {
    ds::unordered_list<int, std::allocator<int>> list(10);

    list[1] = 5;
    list[2] = 15;
    list[5] = 20;

    auto it1 = list.begin();
    auto it2 = list.begin();
    auto it3 = list.end();

    BOOST_CHECK(it1 == it2);  // Check equality
    BOOST_CHECK(it1 != it3);  // Check inequality
    ++it2;
    BOOST_CHECK(it1 != it2);
}

// Test iterator increment and decrement
BOOST_AUTO_TEST_CASE(unordered_list_iterator_increment_decrement_test) {
    ds::unordered_list<int, std::allocator<int>> list(10);

    list[1] = 10;
    list[3] = 20;
    list[5] = 30;

    auto it = list.begin();
    BOOST_CHECK_EQUAL(*it, 10);
    ++it;
    BOOST_CHECK_EQUAL(*it, 20);
    ++it;
    BOOST_CHECK_EQUAL(*it, 30);

    --it;
    BOOST_CHECK_EQUAL(*it, 20);
    --it;
    BOOST_CHECK_EQUAL(*it, 10);
}

// Test iterator arithmetic
BOOST_AUTO_TEST_CASE(unordered_list_iterator_arithmetic_test) {
    ds::unordered_list<int, std::allocator<int>> list(10);

    list[0] = 10;
    list[2] = 20;
    list[4] = 30;

    auto it = list.begin();
    it += 2;
    BOOST_CHECK_EQUAL(*it, 30);  // After moving two steps ahead

    it -= 2;
    BOOST_CHECK_EQUAL(*it, 10);  // After moving two steps back

    auto it2 = it + 2;
    BOOST_CHECK_EQUAL(*it2, 30);

    auto diff = it2 - it;
    BOOST_CHECK_EQUAL(diff, 2);
}

// Test iterator dereference and pointer access
BOOST_AUTO_TEST_CASE(unordered_list_iterator_dereference_test) {
    ds::unordered_list<int, std::allocator<int>> list(10);

    list[0] = 100;
    list[5] = 200;

    auto it = list.begin();
    BOOST_CHECK_EQUAL(*it, 100);  // Dereference the iterator
    BOOST_CHECK_EQUAL(it.operator*(), 100);  // Access pointer
}

// Test for modifying values through iterators
BOOST_AUTO_TEST_CASE(unordered_list_iterator_modify_test) {
    ds::unordered_list<int, std::allocator<int>> list(10);

    list[2] = 50;
    list[4] = 100;

    auto it = list.begin();
    *it = 60;  // Modify through iterator

    BOOST_CHECK_EQUAL(list[2], 60);  // Ensure modification took place
}

// Test iterator boundary conditions (begin and end)
BOOST_AUTO_TEST_CASE(unordered_list_iterator_boundary_test) {
    ds::unordered_list<int, std::allocator<int>> list(10);

    list[2] = 10;
    list[5] = 20;
    list[8] = 30;

    auto it = list.begin();
    BOOST_CHECK(it != list.end());  // Ensure begin != end
    ++it;
    ++it;
    BOOST_CHECK_EQUAL(*it, 30);
    ++it;
    BOOST_CHECK(it == list.end());  // Check that we reached the end
}

// Test range-based for loop to iterate over unordered_list
BOOST_AUTO_TEST_CASE(unordered_list_range_based_for_loop_test) {
    ds::unordered_list<int, std::allocator<int>> list(10);

    // Insert some elements
    list[1] = 10;
    list[3] = 20;
    list[7] = 30;

    std::vector<int> values;
    
    // Use range-based for loop to iterate over unordered_list
    for (const auto& value : list) {
        values.push_back(value);
    }

    BOOST_CHECK_EQUAL(values.size(), 3);
    BOOST_CHECK_EQUAL(values[0], 10);
    BOOST_CHECK_EQUAL(values[1], 20);
    BOOST_CHECK_EQUAL(values[2], 30);
}

// Test regular for loop to iterate over unordered_list
BOOST_AUTO_TEST_CASE(unordered_list_regular_for_loop_test) {
    ds::unordered_list<int, std::allocator<int>> list(10);

    // Insert some elements
    list[2] = 15;
    list[4] = 25;
    list[6] = 35;

    std::vector<int> values;

    // Use a regular for loop with iterators to iterate over unordered_list
    for (auto it = list.begin(); it != list.end(); ++it) {
        values.push_back(*it);
    }

    BOOST_CHECK_EQUAL(values.size(), 3);
    BOOST_CHECK_EQUAL(values[0], 15);
    BOOST_CHECK_EQUAL(values[1], 25);
    BOOST_CHECK_EQUAL(values[2], 35);
}

// Test using std::find with unordered_list
BOOST_AUTO_TEST_CASE(unordered_list_std_find_test) {
    ds::unordered_list<int, std::allocator<int>> list(10);

    // Insert some elements
    list[1] = 100;
    list[3] = 200;
    list[5] = 300;

    // Use std::find to locate an element
    auto it = std::find(list.begin(), list.end(), 200);

    BOOST_CHECK(it != list.end());
    BOOST_CHECK_EQUAL(*it, 200);

    // Try finding an element that does not exist
    it = std::find(list.begin(), list.end(), 500);
    BOOST_CHECK(it == list.end());
}

// Test edge case with empty list and iterating over it
BOOST_AUTO_TEST_CASE(unordered_list_empty_iteration_test) {
    ds::unordered_list<int, std::allocator<int>> list(10);

    // Iterate over an empty list
    std::vector<int> values;
    for (const auto& value : list) {
        values.push_back(value);  // Should not add anything since the list is empty
    }

    BOOST_CHECK_EQUAL(values.size(), 0);
}

// Test edge case where items are added and removed, then iterated
BOOST_AUTO_TEST_CASE(unordered_list_add_remove_iterate_test) {
    ds::unordered_list<int, std::allocator<int>> list(10);

    // Insert some elements
    list[0] = 5;
    list[2] = 10;
    list[4] = 20;

    // Remove some elements by directly clearing the index_set and reinsert
    list[0] = 0;
    list[2] = 15;

    std::vector<int> values;
    for (auto& value : list) {
        values.push_back(value);
    }

    BOOST_CHECK_EQUAL(values.size(), 3);
    BOOST_CHECK_EQUAL(values[0], 0);
    BOOST_CHECK_EQUAL(values[1], 15);
    BOOST_CHECK_EQUAL(values[2], 20);
}


BOOST_AUTO_TEST_CASE(unordered_list_accumulate_test) {
    ds::unordered_list<int, std::allocator<int>> list(10);

    // Insert elements
    list[1] = 1;
    list[3] = 2;
    list[5] = 3;

    // Use std::accumulate to sum the elements in the list
    int sum = std::accumulate(list.begin(), list.end(), 0);

    BOOST_CHECK_EQUAL(sum, 6);  // 1 + 2 + 3
}

// Test for modifying values via range-based for loop
BOOST_AUTO_TEST_CASE(unordered_list_modify_via_range_based_for_loop_test) {
    ds::unordered_list<int, std::allocator<int>> list(10);

    // Insert elements
    list[2] = 50;
    list[5] = 100;
    list[7] = 150;

    // Modify values using a range-based for loop
    for (auto& value : list) {
        value *= 2;  // Double each value
    }

    BOOST_CHECK_EQUAL(list[2], 100);
    BOOST_CHECK_EQUAL(list[5], 200);
    BOOST_CHECK_EQUAL(list[7], 300);
}

// Test shrink_to_fit functionality
BOOST_AUTO_TEST_CASE(unordered_list_shrink_to_fit_test) {
    ds::unordered_list<int, std::allocator<int>> list(10);

    list[2] = 5;
    list[7] = 10;
    list[9] = 15;

    BOOST_CHECK_EQUAL(list.capacity(), 10);  // Initial capacity

    list.shrink_to_fit();  // Adjust capacity

    BOOST_CHECK_EQUAL(list.capacity(), 10);  // Capacity remains the same
    BOOST_CHECK_EQUAL(list.size(), 3);       // Size unchanged
    BOOST_CHECK_EQUAL(list[2], 5);
    BOOST_CHECK_EQUAL(list[7], 10);
    BOOST_CHECK_EQUAL(list[9], 15);
}

// Test shrink_to_fit with reduction in capacity
BOOST_AUTO_TEST_CASE(unordered_list_shrink_to_fit_reduction_test) {
    ds::unordered_list<int, std::allocator<int>> list(15);

    list[1] = 100;
    list[3] = 200;
    list[5] = 300;

    BOOST_CHECK_EQUAL(list.capacity(), 15);  // Initial capacity

    list.shrink_to_fit();  // Should reduce capacity

    BOOST_CHECK_EQUAL(list.capacity(), 6);  // Last index (5) + 1
    BOOST_CHECK_EQUAL(list[1], 100);
    BOOST_CHECK_EQUAL(list[3], 200);
    BOOST_CHECK_EQUAL(list[5], 300);
}


// Test shrink_to_fit with an empty list
BOOST_AUTO_TEST_CASE(unordered_list_shrink_to_fit_empty_list_test) {
    ds::unordered_list<int, std::allocator<int>> list(10);

    BOOST_CHECK_EQUAL(list.capacity(), 10);  // Initial capacity
    list.shrink_to_fit();
    BOOST_CHECK_EQUAL(list.capacity(), 10);  // Capacity shouldn't change if there are no elements
}

 
BOOST_AUTO_TEST_SUITE_END()
