#include <boost/test/unit_test.hpp>
#include "hash_set.hpp"
#include <vector>
#include <string>

BOOST_AUTO_TEST_SUITE(HASH_SET_TEST)

BOOST_AUTO_TEST_CASE(test_empty_set) {
    ds::hash_set<int> set;
    BOOST_CHECK(set.empty());
    BOOST_CHECK_EQUAL(set.size(), 0);
    BOOST_CHECK(set.begin() == set.end());
}

BOOST_AUTO_TEST_CASE(test_single_insertion) {
    ds::hash_set<int> set;
    set.insert(42);
    
    BOOST_CHECK(!set.empty());
    BOOST_CHECK_EQUAL(set.size(), 1);
    BOOST_CHECK(set.contains(42));
    BOOST_CHECK(set.find(42) != set.end());
}

BOOST_AUTO_TEST_CASE(test_multiple_insertions) {
    ds::hash_set<int> set;
    set.insert(1);
    set.insert(2);
    set.insert(3);

    BOOST_CHECK_EQUAL(set.size(), 3);
    BOOST_CHECK(set.contains(1));
    BOOST_CHECK(set.contains(2));
    BOOST_CHECK(set.contains(3));
}

BOOST_AUTO_TEST_CASE(test_erase_existing_element) {
    ds::hash_set<int> set;
    set.insert(10);
    set.insert(20);
    set.erase(10);

    BOOST_CHECK_EQUAL(set.size(), 1);
    BOOST_CHECK(!set.contains(10));
    BOOST_CHECK(set.contains(20));
}

BOOST_AUTO_TEST_CASE(test_erase_nonexistent_element) {
    ds::hash_set<int> set;
    set.insert(1);
    set.erase(42);  // Erase a key that doesn't exist

    BOOST_CHECK_EQUAL(set.size(), 1);  // Size remains unchanged
    BOOST_CHECK(set.contains(1));
}

BOOST_AUTO_TEST_CASE(test_clear_set) {
    ds::hash_set<int> set;
    set.insert(1);
    set.insert(2);
    set.clear();

    BOOST_CHECK(set.empty());
    BOOST_CHECK_EQUAL(set.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_iterator_traversal) {
    ds::hash_set<int> set{1, 2, 3};

    std::vector<int> elements;
    for (auto it = set.begin(); it != set.end(); ++it) {
        elements.push_back(*it);
    }

    BOOST_CHECK_EQUAL(elements.size(), 3);
    BOOST_CHECK(std::find(elements.begin(), elements.end(), 1) != elements.end());
    BOOST_CHECK(std::find(elements.begin(), elements.end(), 2) != elements.end());
    BOOST_CHECK(std::find(elements.begin(), elements.end(), 3) != elements.end());
}

BOOST_AUTO_TEST_CASE(test_const_iterator_traversal) {
    const ds::hash_set<int> set{10, 20, 30};

    std::vector<int> elements;
    for (auto it = set.cbegin(); it != set.cend(); ++it) {
        elements.push_back(*it);
    }

    BOOST_CHECK_EQUAL(elements.size(), 3);
    BOOST_CHECK(std::find(elements.begin(), elements.end(), 10) != elements.end());
    BOOST_CHECK(std::find(elements.begin(), elements.end(), 20) != elements.end());
    BOOST_CHECK(std::find(elements.begin(), elements.end(), 30) != elements.end());
}

BOOST_AUTO_TEST_CASE(test_find_iterator_valid) {
    ds::hash_set<std::string> set;
    set.insert("hello");

    auto it = set.find("hello");
    BOOST_CHECK(it != set.end());
    BOOST_CHECK_EQUAL(*it, "hello");
}

BOOST_AUTO_TEST_CASE(test_find_iterator_invalid) {
    ds::hash_set<int> set;
    set.insert(1);

    auto it = set.find(42);
    BOOST_CHECK(it == set.end());  // Non-existent element
}

BOOST_AUTO_TEST_CASE(test_reserve_and_rehash) {
    ds::hash_set<int> set;
    set.reserve(50);

    BOOST_CHECK_GE(set.capacity(), 50);  // Ensure capacity is at least 50

    set.insert(1);
    set.insert(2);
    set.insert(3);

    BOOST_CHECK_EQUAL(set.size(), 3);
    BOOST_CHECK(set.contains(1));
}

BOOST_AUTO_TEST_CASE(test_max_load_factor) {
    ds::hash_set<int> set;
    set.max_load_factor(0.5f);  // Set load factor to a low value to trigger rehash sooner

    set.insert(1);
    set.insert(2);
    set.insert(3);  // Should trigger rehash

    BOOST_CHECK(set.contains(1));
    BOOST_CHECK(set.contains(2));
    BOOST_CHECK(set.contains(3));
}

BOOST_AUTO_TEST_CASE(test_edge_case_large_number_of_elements) {
    ds::hash_set<int> set;
    for (int i = 0; i < 10000; ++i) {
        set.insert(i);
    }

    BOOST_CHECK_EQUAL(set.size(), 10000);
    BOOST_CHECK(set.contains(9999));
}

BOOST_AUTO_TEST_CASE(test_duplicated_insertion) {
    ds::hash_set<int> set;
    set.insert(1);
    set.insert(1);  // Insert the same element twice

    BOOST_CHECK_EQUAL(set.size(), 1);  // Size should remain 1
}

BOOST_AUTO_TEST_CASE(test_begin_end_consistency) {
    ds::hash_set<int> set{1, 2, 3};
    BOOST_CHECK(set.begin() != set.end());  // Non-empty set

    set.clear();
    BOOST_CHECK(set.begin() == set.end());  // After clear, begin == end
}

BOOST_AUTO_TEST_SUITE_END()