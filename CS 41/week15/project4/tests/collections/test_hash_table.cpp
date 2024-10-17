#include <boost/test/unit_test.hpp> 
#include "hash_table.hpp"

BOOST_AUTO_TEST_SUITE(HASH_TABLE_TEST)

// Test for basic initialization
BOOST_AUTO_TEST_CASE(init_test) {
    ds::hash_table<int, int> table;
    BOOST_CHECK_EQUAL(table.load_factor(), 0.0);
}

BOOST_AUTO_TEST_CASE(hash_table_copy_test){
    ds::hash_table<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 30);

    ds::hash_table<int, int> table2(table);
    BOOST_CHECK_EQUAL(table2[1], 10);
    BOOST_CHECK_EQUAL(table2[2], 20);
    BOOST_CHECK_EQUAL(table2[3], 30);
    BOOST_CHECK_EQUAL(table[1], 10);
    BOOST_CHECK_EQUAL(table[2], 20);
    BOOST_CHECK_EQUAL(table[3], 30);
}

BOOST_AUTO_TEST_CASE(hash_table_move_test){
    ds::hash_table<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 30);

    ds::hash_table<int, int> table2(std::move(table));
    BOOST_CHECK_EQUAL(table2[1], 10);
    BOOST_CHECK_EQUAL(table2[2], 20);
    BOOST_CHECK_EQUAL(table2[3], 30);
    BOOST_CHECK(table.empty());
}

BOOST_AUTO_TEST_CASE(hash_table_copy_assignment_test){
    ds::hash_table<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 30);

    ds::hash_table<int, int> table2;
    table2 = table;
    BOOST_CHECK_EQUAL(table2[1], 10);
    BOOST_CHECK_EQUAL(table2[2], 20);
    BOOST_CHECK_EQUAL(table2[3], 30);
    BOOST_CHECK_EQUAL(table[1], 10);
    BOOST_CHECK_EQUAL(table[2], 20);
    BOOST_CHECK_EQUAL(table[3], 30);
}

BOOST_AUTO_TEST_CASE(hash_table_move_assignment_test){
    ds::hash_table<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 30);

    ds::hash_table<int, int> table2;
    table2 = std::move(table);
    BOOST_CHECK_EQUAL(table2[1], 10);
    BOOST_CHECK_EQUAL(table2[2], 20);
    BOOST_CHECK_EQUAL(table2[3], 30);
    BOOST_CHECK(table.empty());
}

BOOST_AUTO_TEST_CASE(hash_table_initializer_list_test){
    ds::hash_table<int, int> table = {{1, 10}, {2, 20}, {3, 30}};
    BOOST_CHECK_EQUAL(table[1], 10);
    BOOST_CHECK_EQUAL(table[2], 20);
    BOOST_CHECK_EQUAL(table[3], 30);
    BOOST_CHECK_EQUAL(table.size(), 3);
}
// Test insertion with different overloads
BOOST_AUTO_TEST_CASE(hash_table_insert_test){
    ds::hash_table<int, int> table;
    table.insert(1, 10);
    table.insert({2, 20});
    table.emplace(3, 30);

    BOOST_CHECK_EQUAL(table[1], 10);
    BOOST_CHECK_EQUAL(table[2], 20);
    BOOST_CHECK_EQUAL(table[3], 30);
}

// Test emplace method with non-trivial types
BOOST_AUTO_TEST_CASE(hash_table_emplace_test){
    ds::hash_table<std::string, int> table;
    table.emplace("key1", 10);
    table.emplace("key2", 20);
    table.emplace("key3", 30);

    BOOST_CHECK_EQUAL(table["key1"], 10);
    BOOST_CHECK_EQUAL(table["key2"], 20);
    BOOST_CHECK_EQUAL(table["key3"], 30);
}

// Test at() method for valid and invalid access
BOOST_AUTO_TEST_CASE(hash_table_at_test){
    ds::hash_table<int, int> table;
    table.emplace(1, 10);
    table.emplace(2, 20);

    BOOST_CHECK_EQUAL(table.at(1), 10);
    BOOST_CHECK_EQUAL(table.at(2), 20);
    BOOST_CHECK_THROW(table.at(3), std::out_of_range);
}

// Test erase method and behavior after deletion
BOOST_AUTO_TEST_CASE(hash_table_remove_test){
    ds::hash_table<int, int> table;
    table.emplace(1, 10);
    table.emplace(2, 20);
    table.emplace(3, 30);
    table.erase(2);

    BOOST_CHECK_THROW(table.at(2), std::out_of_range);
    BOOST_CHECK_EQUAL(table.at(1), 10);
    BOOST_CHECK_EQUAL(table.at(3), 30);
}

// Test for rehashing and behavior under high load
BOOST_AUTO_TEST_CASE(hash_table_rehash_test) {
    ds::hash_table<int, int> table(2);
    table.max_load_factor(0.5);  // Trigger rehashing earlier

    table.emplace(1, 10);
    table.emplace(2, 20);
    table.emplace(3, 30);  // Should trigger a rehash

    BOOST_CHECK_EQUAL(table[1], 10);
    BOOST_CHECK_EQUAL(table[2], 20);
    BOOST_CHECK_EQUAL(table[3], 30);
    BOOST_CHECK_GT(table.load_factor(), 0.0); // Ensure load factor updated
}
 
BOOST_AUTO_TEST_CASE(hash_table_insert_or_assign_test) {
    ds::hash_table<int, int> table;
    table.insert_or_assign(1, 10);
    BOOST_CHECK_EQUAL(table[1], 10);

    table.insert_or_assign(1, 20);  // Should update the value
    BOOST_CHECK_EQUAL(table[1], 20);
}

// Test behavior with custom hash and key comparison functions
BOOST_AUTO_TEST_CASE(hash_table_custom_hash_test) {
    struct ModHash {
        size_t operator()(int key) const {
            return size_t(key % 10);
        }
    };

    ds::hash_table<int, int, ModHash> table;
    table.insert(1, 10);
    table.insert(11, 20);  // Will collide with key 1

    BOOST_CHECK_EQUAL(table[1], 10);
    BOOST_CHECK_EQUAL(table[11], 20);
}

// Test edge cases with an empty table
BOOST_AUTO_TEST_CASE(hash_table_empty_test) {
    ds::hash_table<int, int> table;

    BOOST_CHECK_THROW(table.at(1), std::out_of_range);  // Accessing empty table
    BOOST_CHECK_EQUAL(table.load_factor(), 0.0);

    table.clear();  // Ensure no exception on clear
}

BOOST_AUTO_TEST_CASE(check_contains_test){
    ds::hash_table<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 30);

    BOOST_CHECK(table.contains(1));
    BOOST_CHECK(table.contains(2));
    BOOST_CHECK(table.contains(3));
    BOOST_CHECK(!table.contains(4));
}
//Test iterator functionality and traversal
BOOST_AUTO_TEST_CASE(hash_table_iterator_test) {
    ds::hash_table<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 30);
    
    BOOST_CHECK_EQUAL(table.size(), 3);

    auto it = table.begin();
    size_t count = 0;
    while (it != table.end()) {
        ++it;
        ++count;
    }
    BOOST_CHECK_EQUAL(count, 3);
}

// Test insertion and size/capacity
BOOST_AUTO_TEST_CASE(test_hash_table_insert_and_size) {
    ds::hash_table<int, int> table;

    BOOST_CHECK(table.empty());
    BOOST_CHECK_EQUAL(table.size(), 0);

    table.insert(1, 100);
    table.insert(2, 200);
    table.insert(3, 300);

    BOOST_CHECK_EQUAL(table.size(), 3);
    BOOST_CHECK(table.capacity() >= 3);
    BOOST_CHECK(!table.empty());
}

// Test non-const iterator traversal
BOOST_AUTO_TEST_CASE(test_hash_table_non_const_iterator) {
    ds::hash_table<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 30);

    std::vector<int> keys;
    for (auto it = table.begin(); it != table.end(); ++it) {
        keys.push_back(it->first);
    }

    BOOST_CHECK_EQUAL(keys.size(), 3);
    BOOST_CHECK(std::find(keys.begin(), keys.end(), 1) != keys.end());
    BOOST_CHECK(std::find(keys.begin(), keys.end(), 2) != keys.end());
    BOOST_CHECK(std::find(keys.begin(), keys.end(), 3) != keys.end());
}

// Test const iterator traversal
BOOST_AUTO_TEST_CASE(test_hash_table_const_iterator) {
    ds::hash_table<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 30);

    const auto& const_table = table;
    std::vector<int> values;

    for (auto it = const_table.cbegin(); it != const_table.cend(); ++it) {
        values.push_back(it->second);
    }

    BOOST_CHECK_EQUAL(values.size(), 3);
    BOOST_CHECK(std::find(values.begin(), values.end(), 10) != values.end());
    BOOST_CHECK(std::find(values.begin(), values.end(), 20) != values.end());
    BOOST_CHECK(std::find(values.begin(), values.end(), 30) != values.end());
}

// Test contains method
BOOST_AUTO_TEST_CASE(test_hash_table_contains) {
    ds::hash_table<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);

    BOOST_CHECK(table.contains(1));
    BOOST_CHECK(table.contains(2));
    BOOST_CHECK(!table.contains(3));
}

// Test find method
BOOST_AUTO_TEST_CASE(test_hash_table_find) {
    ds::hash_table<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);

    auto it = table.find(1);
    BOOST_CHECK(it != table.end());
    BOOST_CHECK_EQUAL(it->second, 10);

    it = table.find(3);
    BOOST_CHECK(it == table.end());
}

// Test capacity and max load factor
BOOST_AUTO_TEST_CASE(test_hash_table_capacity_and_rehash) {
    ds::hash_table<int, int> table(2);
    BOOST_CHECK_EQUAL(table.capacity(), 2);

    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 30);  // Triggers rehash

    BOOST_CHECK(table.capacity() >= 3);
}

// Test edge case: Empty table with iterators
BOOST_AUTO_TEST_CASE(test_hash_table_empty_iterators) {
    ds::hash_table<int, int> table;
    BOOST_CHECK(table.begin() == table.end());
    BOOST_CHECK(table.cbegin() == table.cend());
}

// Test clearing the table
BOOST_AUTO_TEST_CASE(test_hash_table_clear) {
    ds::hash_table<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);
    table.clear();

    BOOST_CHECK(table.empty());
    BOOST_CHECK_EQUAL(table.size(), 0);
    BOOST_CHECK(table.begin() == table.end());
}

// Test inserting duplicate keys
BOOST_AUTO_TEST_CASE(test_hash_table_duplicate_keys) {
    ds::hash_table<int, int> table;
    table.insert(1, 10);
    table.insert(1, 20);  // Should not replace the value

    auto it = table.find(1);
    BOOST_CHECK_EQUAL(it->second, 10);  // Value should still be 10
}

// Test find with non-existent key
BOOST_AUTO_TEST_CASE(test_hash_table_find_non_existent) {
    ds::hash_table<int, int> table;
    table.insert(1, 10);

    auto it = table.find(2);  // Key 2 does not exist
    BOOST_CHECK(it == table.end());
}

// Test iteration over an empty table
BOOST_AUTO_TEST_CASE(test_hash_table_iteration_empty) {
    ds::hash_table<int, int> table;

    size_t count = 0;
    for (auto it = table.begin(); it != table.end(); ++it) {
        ++count;
    }

    BOOST_CHECK_EQUAL(count, 0);
}

// Test large insertion to ensure stability with many elements
BOOST_AUTO_TEST_CASE(test_hash_table_large_insertion) {
    ds::hash_table<int, int> table;
    int num_elements = 10000;

    for (int i = 0; i < num_elements; ++i) {
        table.insert(i, i * 10);
    }

    BOOST_CHECK_EQUAL(table.size(), num_elements);

    for (int i = 0; i < num_elements; ++i) {
        BOOST_CHECK_EQUAL(table.at(i), i * 10);
    }
}

// Test reserve method and ensure no rehash occurs unnecessarily
BOOST_AUTO_TEST_CASE(test_hash_table_reserve) {
    ds::hash_table<int, int> table;
    table.reserve(2000);  // Reserve space for 2000 elements

    BOOST_CHECK_GE(table.capacity(), 2000);
    BOOST_CHECK(table.empty());

    // Insert a few elements and verify no rehash occurs prematurely
    table.insert(1, 10);
    table.insert(2, 20);
    BOOST_CHECK_EQUAL(table.size(), 2);
}

// Test rehashing under load
BOOST_AUTO_TEST_CASE(test_hash_table_rehash_under_load) {
    ds::hash_table<int, int> table(10);
    table.max_load_factor(0.75);  // Set a low max load factor to trigger rehashing sooner

    // Insert elements and ensure rehash occurs
    for (int i = 0; i < 20; ++i) {
        table.insert(i, i * 2);
    }

    BOOST_CHECK(table.capacity() > 10);  // Verify that capacity increased
    BOOST_CHECK_EQUAL(table.size(), 20);

    for (int i = 0; i < 20; ++i) {
        BOOST_CHECK_EQUAL(table.at(i), i * 2);
    }
}

// Test behavior when rehashing is triggered with many elements
BOOST_AUTO_TEST_CASE(test_hash_table_rehash_many_elements) {
    ds::hash_table<int, int> table;

    // Insert a large number of elements
    for (int i = 0; i < 1000; ++i) {
        table.insert(i, i * 3);
    }

    BOOST_CHECK_EQUAL(table.size(), 1000);

    // Trigger rehash by setting a low max load factor
    table.max_load_factor(0.1f);
    table.rehash(2000);  // Explicit rehash to larger capacity

    BOOST_CHECK_GE(table.capacity(), 2000);

    // Verify all elements are still accessible
    for (int i = 0; i < 1000; ++i) {
        BOOST_CHECK_EQUAL(table.at(i), i * 3);
    }
}

BOOST_AUTO_TEST_SUITE_END()