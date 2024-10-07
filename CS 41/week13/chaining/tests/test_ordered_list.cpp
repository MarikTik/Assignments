#include <boost/test/unit_test.hpp>
#include "ordered_list.hpp"

#include <boost/test/unit_test.hpp>
#include "ordered_list.hpp"

BOOST_AUTO_TEST_SUITE(ORDERED_LIST_TEST)

// Test push_back for basic functionality using iterators
BOOST_AUTO_TEST_CASE(ordered_list_push_back_test) {
    ds::ordered_list<int> list(2);

    // Test adding elements
    list.push_back(1);
    list.push_back(2);
    list.push_back(3); // Test automatic resizing

    auto it = list.begin();
    BOOST_CHECK_EQUAL(*it, 1);
    ++it;
    BOOST_CHECK_EQUAL(*it, 2);
    ++it;
    BOOST_CHECK_EQUAL(*it, 3);
}

// Test remove by predicate functionality using iterators
// BOOST_AUTO_TEST_CASE(ordered_list_remove_test) {
//     ds::ordered_list<int> list(4);

//     // Add elements
//     list.push_back(1);
//     list.push_back(2);
//     list.push_back(3);
//     list.push_back(4);

//     // Remove first even number
//     list.remove([](int x) noexcept { return x % 2 == 0; });
    
//     auto it = list.begin();
//     BOOST_CHECK_EQUAL(*it, 1);
//     ++it;
//     BOOST_CHECK_EQUAL(*it, 3);
//     ++it;
//     BOOST_CHECK_EQUAL(*it, 4);

//     // Remove all odd numbers
//     list.remove([](int x) noexcept { return x % 2 != 0; }, 0);

//     it = list.begin();
//     BOOST_CHECK_EQUAL(*it, 4);
// }

// Test iterator increment and decrement
BOOST_AUTO_TEST_CASE(iterator_increment_decrement_test) {
    ds::ordered_list<int> list(5);

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    ds::ordered_list<int>::iterator it = list.begin();

    // Test prefix increment
    BOOST_CHECK_EQUAL(*++it, 20);
    BOOST_CHECK_EQUAL(*++it, 30);

    // Test postfix increment
    it = list.begin();
    BOOST_CHECK_EQUAL(*it++, 10);
    BOOST_CHECK_EQUAL(*it++, 20);
    BOOST_CHECK_EQUAL(*it, 30);

    // Test prefix decrement
    BOOST_CHECK_EQUAL(*--it, 20);
    BOOST_CHECK_EQUAL(*--it, 10);

    // Test postfix decrement
    it = list.end();
    --it; // Move back from end to valid position
    BOOST_CHECK_EQUAL(*it--, 30);
    BOOST_CHECK_EQUAL(*it--, 20);
    BOOST_CHECK_EQUAL(*it, 10);
}

// Test iterator comparison operations
BOOST_AUTO_TEST_CASE(iterator_comparison_test) {
    ds::ordered_list<int> list(3);

    list.push_back(100);
    list.push_back(200);
    list.push_back(300);

    auto it1 = list.begin();
    auto it2 = list.begin();

    BOOST_CHECK(it1 == it2);
    ++it2;
    BOOST_CHECK(it1 != it2);
    BOOST_CHECK(it1 < it2);
    BOOST_CHECK(it2 > it1);

    // Test <= and >= operators
    BOOST_CHECK(it1 <= it2);
    BOOST_CHECK(it2 >= it1);

    ++it1;
    BOOST_CHECK(it1 == it2);
}

// Test iterator arithmetic operations
BOOST_AUTO_TEST_CASE(iterator_arithmetic_test) {
    ds::ordered_list<int> list(5);

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);
    list.push_back(50);

    auto it = list.begin();
    it += 2;
    BOOST_CHECK_EQUAL(*it, 30);

    it -= 1;
    BOOST_CHECK_EQUAL(*it, 20);

    auto it2 = it + 2;
    BOOST_CHECK_EQUAL(*it2, 40);

    it2 = it2 - 2;
    BOOST_CHECK_EQUAL(*it2, 20);

    auto distance = it2 - list.begin();
    BOOST_CHECK_EQUAL(distance, 1);
}

// Test removing elements via iterator
BOOST_AUTO_TEST_CASE(iterator_remove_test) {
    ds::ordered_list<int> list(5);

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    auto it = list.begin();
    ++it;  // Point to second element (20)
    list.remove(it);  // Remove the element at iterator position

    it = list.begin();
    BOOST_CHECK_EQUAL(*it++, 10);
    BOOST_CHECK_EQUAL(*it++, 30);
    BOOST_CHECK(it == list.end());  // List should now have only two elements
}

BOOST_AUTO_TEST_SUITE_END()
