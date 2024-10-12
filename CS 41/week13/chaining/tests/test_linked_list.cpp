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
    destination.insert_range(source.begin(), source.end());

    BOOST_CHECK_EQUAL(destination.size(), 3);
    auto it = destination.begin();
    BOOST_CHECK_EQUAL(*it, 1);
    BOOST_CHECK_EQUAL(*(++it), 2);
    BOOST_CHECK_EQUAL(*(++it), 3);
}

BOOST_AUTO_TEST_CASE(test_const_iterator) {
    ds::linked_list<int> list;
    list.push_back(1);
    list.push_back(2);

    const auto& const_list = list;
    auto it = const_list.cbegin();
    BOOST_CHECK_EQUAL(*it, 1);
    BOOST_CHECK_EQUAL(*(++it), 2);
    BOOST_CHECK(++it == const_list.cend());
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

BOOST_AUTO_TEST_SUITE_END()
