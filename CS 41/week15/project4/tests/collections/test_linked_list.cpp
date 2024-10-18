#include <boost/test/unit_test.hpp>
#include "linked_list.hpp"

// Custom class to test emplace with constructor arguments
struct TestObject {
    int a;
    double b;

    TestObject(int _a, double _b) : a(_a), b(_b) {}
};

BOOST_AUTO_TEST_SUITE(LINKED_LIST_TEST)

BOOST_AUTO_TEST_CASE(test_initialization) {
    ds::linked_list<int> list;
    BOOST_CHECK(list.empty());
    BOOST_CHECK_EQUAL(list.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_empty_destructor) {
    ds::linked_list<int> list;
    class T {};
    ds::linked_list<T> list2;
}

BOOST_AUTO_TEST_CASE(test_list_move_constructor) {
    ds::linked_list<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    ds::linked_list<int> list2{std::move(list)};
    BOOST_CHECK(list.empty());
    BOOST_CHECK_EQUAL(list2.size(), 3);
    auto it = list2.begin();
    BOOST_CHECK_EQUAL(*it, 1);
    BOOST_CHECK_EQUAL(*(++it), 2);
    BOOST_CHECK_EQUAL(*(++it), 3);
    BOOST_CHECK(++it == list2.end());
}

BOOST_AUTO_TEST_CASE(test_list_move_assignment) {
    ds::linked_list<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    ds::linked_list<int> list2;
    list2 = std::move(list);
    BOOST_CHECK(list.empty());
    BOOST_CHECK_EQUAL(list2.size(), 3);

    auto it = list2.begin();
    BOOST_CHECK_EQUAL(*it, 1);
    BOOST_CHECK_EQUAL(*(++it), 2);
    BOOST_CHECK_EQUAL(*(++it), 3);
    BOOST_CHECK(++it == list2.end());
}

BOOST_AUTO_TEST_CASE(test_emplace_with_custom_object) {
    ds::linked_list<TestObject> list;
    list.emplace_back(1, 2.5);
    list.emplace_back(2, 3.5);

    auto it = list.begin();
    BOOST_CHECK_EQUAL(it->a, 1);
    BOOST_CHECK_EQUAL(it->b, 2.5);
    BOOST_CHECK_EQUAL((++it)->a, 2);
    BOOST_CHECK_EQUAL(it->b, 3.5);
}

BOOST_AUTO_TEST_CASE(test_push_back_single) {
    ds::linked_list<int> list;
    list.push_back(1);
    BOOST_CHECK(not list.empty());
    BOOST_CHECK_EQUAL(list.size(), 1);

    auto it = list.begin();
    BOOST_CHECK_EQUAL(*it, 1);
    BOOST_CHECK(++it == list.end());
}

BOOST_AUTO_TEST_CASE(test_push_front_single) {
    ds::linked_list<int> list;
    list.push_front(1);
    BOOST_CHECK(not list.empty());

    auto it = list.begin();
    BOOST_CHECK_EQUAL(*it, 1);
    BOOST_CHECK(++it == list.end());
}

BOOST_AUTO_TEST_CASE(test_insert_range) {
    ds::linked_list<int> source;
    source.push_back(1);
    source.push_back(2);
    source.push_back(3);

    ds::linked_list<int> destination;
    destination.insert_front(source.begin(), source.end());

    BOOST_CHECK_EQUAL(destination.size(), 3);
    auto it = destination.begin();
    BOOST_CHECK_EQUAL(*it, 1);
    BOOST_CHECK_EQUAL(*(++it), 2);
    BOOST_CHECK_EQUAL(*(++it), 3);
}
 
BOOST_AUTO_TEST_CASE(test_clear) {
    ds::linked_list<int> list;
    list.push_front(1);
    list.push_back(2);
    list.push_front(3);
    list.push_back(4);

    list.clear();
    BOOST_CHECK(list.empty());
    BOOST_CHECK_EQUAL(list.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_erase) {
    ds::linked_list<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto it = list.begin();
    list.erase(it);  // Remove first element (1)
    BOOST_CHECK_EQUAL(list.size(), 2);
    BOOST_CHECK_EQUAL(*list.begin(), 2);

    it = list.erase(list.begin());  // Remove second element (2)
    BOOST_CHECK_EQUAL(list.size(), 1);
    BOOST_CHECK_EQUAL(*it, 3);

    list.erase(it);  // Remove last element (3)
    BOOST_CHECK(list.empty());
}

BOOST_AUTO_TEST_CASE(test_push_from_both_sides) {
    ds::linked_list<int> list;
    list.push_front(1);
    list.push_back(2);
    list.push_front(3);
    list.push_back(4);

    BOOST_CHECK(not list.empty());
    auto it = list.begin();
    BOOST_CHECK_EQUAL(*it, 3);
    BOOST_CHECK_EQUAL(*(++it), 1);
    BOOST_CHECK_EQUAL(*(++it), 2);
    BOOST_CHECK_EQUAL(*(++it), 4);
    BOOST_CHECK(++it == list.end());
}

BOOST_AUTO_TEST_CASE(test_const_iterator_basic) {
    ds::linked_list<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    const auto& const_list = list;
    auto it = const_list.cbegin();

    BOOST_CHECK_EQUAL(*it, 10);
    BOOST_CHECK_EQUAL(*(++it), 20);
    BOOST_CHECK_EQUAL(*(++it), 30);
    BOOST_CHECK(++it == const_list.cend());
}

// Test const range-based for loop
BOOST_AUTO_TEST_CASE(test_const_iterator_range_based_for_loop) {
    ds::linked_list<int> list;
    list.push_back(5);
    list.push_back(10);
    list.push_back(15);

    const auto& const_list = list;
    std::vector<int> values;

    for (const auto& value : const_list) {
        values.push_back(value);
    }

    BOOST_CHECK_EQUAL(values.size(), 3);
    BOOST_CHECK_EQUAL(values[0], 5);
    BOOST_CHECK_EQUAL(values[1], 10);
    BOOST_CHECK_EQUAL(values[2], 15);
}

// Test inserting and iterating over empty list
BOOST_AUTO_TEST_CASE(test_const_iterator_empty_list) {
    const ds::linked_list<int> list;
    BOOST_CHECK(list.empty());
    BOOST_CHECK(list.cbegin() == list.cend());

    std::vector<int> values;
    for (const auto& value : list) {
        values.push_back(value);
    }

    BOOST_CHECK(values.empty());
}

// Test const_iterator after clearing the list
BOOST_AUTO_TEST_CASE(test_const_iterator_after_clear) {
    ds::linked_list<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.clear();
    const auto& const_list = list;

    BOOST_CHECK(const_list.empty());
    BOOST_CHECK(const_list.cbegin() == const_list.cend());
}

// Test const_iterator with custom objects
BOOST_AUTO_TEST_CASE(test_const_iterator_with_custom_object) {
    ds::linked_list<TestObject> list;
    list.emplace_back(1, 2.5);
    list.emplace_back(2, 3.5);

    const auto& const_list = list;
    auto it = const_list.cbegin();

    BOOST_CHECK_EQUAL(it->a, 1);
    BOOST_CHECK_EQUAL(it->b, 2.5);
    ++it;
    BOOST_CHECK_EQUAL(it->a, 2);
    BOOST_CHECK_EQUAL(it->b, 3.5);
}

// Test const_iterator comparison
BOOST_AUTO_TEST_CASE(test_const_iterator_comparison) {
    ds::linked_list<int> list;
    list.push_back(10);
    list.push_back(20);

    const auto& const_list = list;
    auto it1 = const_list.cbegin();
    auto it2 = const_list.cbegin();

    BOOST_CHECK(it1 == it2);
    ++it2;
    BOOST_CHECK(it1 != it2);
}

// Test edge case: List with one element
BOOST_AUTO_TEST_CASE(test_const_iterator_single_element) {
    ds::linked_list<int> list;
    list.push_back(42);

    const auto& const_list = list;
    auto it = const_list.cbegin();

    BOOST_CHECK_EQUAL(*it, 42);
    ++it;
    BOOST_CHECK(it == const_list.cend());
}


BOOST_AUTO_TEST_SUITE_END()
