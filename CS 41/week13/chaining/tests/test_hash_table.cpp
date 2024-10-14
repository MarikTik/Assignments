#include <boost/test/unit_test.hpp> 
#include "hash_table.hpp"

BOOST_AUTO_TEST_SUITE(HASH_TABLE_TEST)

BOOST_AUTO_TEST_CASE(init_test) {
    ds::hash_table<int, int> table;
}
BOOST_AUTO_TEST_CASE(hash_table_insert_test){
    ds::hash_table<int, int> table;
    table.insert({1, 10});
    table.insert({2, 20});
    table.insert({3, 30});
    BOOST_CHECK_EQUAL(table[1], 10);
    BOOST_CHECK_EQUAL(table[2], 20);
    BOOST_CHECK_EQUAL(table[3], 30);
}

BOOST_AUTO_TEST_CASE(hash_table_emplace_test){
    ds::hash_table<int, int> table;
    table.emplace(1, 10);
    table.emplace(2, 20);
    table.emplace(3, 30);
    BOOST_CHECK_EQUAL(table[1], 10);
    BOOST_CHECK_EQUAL(table[2], 20);
    BOOST_CHECK_EQUAL(table[3], 30);
}

BOOST_AUTO_TEST_CASE(hash_table_at_test){
    ds::hash_table<int, int> table;
    table.emplace(1, 10);
    table.emplace(2, 20);
    table.emplace(3, 30);
    BOOST_CHECK_EQUAL(table.at(1), 10);
    BOOST_CHECK_EQUAL(table.at(2), 20);
    BOOST_CHECK_EQUAL(table.at(3), 30);
}

BOOST_AUTO_TEST_CASE(hash_table_remove_test){
    ds::hash_table<int, int> table;
    table.emplace(1, 10);
    table.emplace(2, 20);
    table.emplace(3, 30);
    table.remove(1);
    BOOST_CHECK_THROW(table.at(1), std::out_of_range);
    BOOST_CHECK_EQUAL(table.at(2), 20);
    BOOST_CHECK_EQUAL(table.at(3), 30);
}

BOOST_AUTO_TEST_SUITE_END()