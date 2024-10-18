#include <boost/test/unit_test.hpp>
#include <limits>
#include "index_set.hpp"

BOOST_AUTO_TEST_SUITE(INDEX_SET_TEST)
constexpr size_t word_size = std::numeric_limits<std::size_t>::digits;

BOOST_AUTO_TEST_CASE(index_set_zero_test) {
    constexpr size_t size = 100;
    ds::_utils::index_set set{size};
    for (size_t i = 0; i < size * word_size; i++) {
        BOOST_CHECK(!set.test(i));
        BOOST_CHECK(!set[i]);
    }
}

BOOST_AUTO_TEST_CASE(index_set_reset_test) {
    ds::_utils::index_set set(2);  // Allocate some capacity for testing

    set.set(10);
    set.set(50);
    set.set(75);

    BOOST_CHECK(set.test(10));
    BOOST_CHECK(set[10]);
    BOOST_CHECK(set.test(50));
    BOOST_CHECK(set.test(75));

    set.reset(10);
    set.reset(50);

    BOOST_CHECK(!set.test(10));
    BOOST_CHECK(!set[10]);
    BOOST_CHECK(!set.test(50));
    BOOST_CHECK(set.test(75));  // Ensure unaffected bit remains set
}

BOOST_AUTO_TEST_CASE(index_set_test_method) {
    ds::_utils::index_set set(2);  // Allocate some capacity

    set.set(20);
    set.set(40);

    BOOST_CHECK(set.test(20));
    BOOST_CHECK(set.test(40));
    BOOST_CHECK(!set.test(21));
    BOOST_CHECK(!set.test(39));
    BOOST_CHECK(!set.test(50));
}

BOOST_AUTO_TEST_CASE(index_set_index_operator_test) {
    ds::_utils::index_set set(2);  // Allocate some capacity

    set.set(5);
    set.set(15);
    set.set(25);

    BOOST_CHECK(set[5]);
    BOOST_CHECK(set[15]);
    BOOST_CHECK(set[25]);

    set.reset(15);
    BOOST_CHECK(!set[15]);
    BOOST_CHECK(set[5]);
    BOOST_CHECK(!set[20]);
    BOOST_CHECK(set[25]);
}

BOOST_AUTO_TEST_CASE(index_set_boundary_test) {
    ds::_utils::index_set set(128);  // Allocate some capacity

    set.set(128 * word_size - 1);
    BOOST_CHECK_THROW(set.set(128 * word_size), std::out_of_range);

    BOOST_CHECK(set.test(128 * word_size - 1));
    BOOST_CHECK(!set.test(128 * word_size + 1));

}

BOOST_AUTO_TEST_CASE(index_set_large_index_test) {
    ds::_utils::index_set set(200);

    size_t largeIndex = 10000;
    set.set(largeIndex);

    BOOST_CHECK(set.test(largeIndex));
    BOOST_CHECK(!set.test(largeIndex - 1));
    BOOST_CHECK(!set.test(largeIndex + 1));
}

BOOST_AUTO_TEST_CASE(index_set_reallocation_test) {
    ds::_utils::index_set set(200);

    size_t largeIndex = 10000;
    set.set(largeIndex);

    BOOST_CHECK(set.test(largeIndex));
}

BOOST_AUTO_TEST_CASE(index_set_exception_test) {
    ds::_utils::index_set set(1);

    BOOST_CHECK_THROW(set.set(200), std::out_of_range);
    BOOST_CHECK_THROW(set.reset(200), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_index_set_size) {
    ds::_utils::index_set set(2);

    set.set(5);
    set.set(15);
    set.set(25);

    BOOST_CHECK_EQUAL(set.count(), 3);

    set.reset(15);
    BOOST_CHECK_EQUAL(set.count(), 2);

    set.reset(5);
    set.reset(25);
    BOOST_CHECK_EQUAL(set.count(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
