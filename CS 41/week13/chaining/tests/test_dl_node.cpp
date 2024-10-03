#include <boost/test/unit_test.hpp>
#include "dl_node.hpp"

BOOST_AUTO_TEST_SUITE(DL_NODE_TEST)

BOOST_AUTO_TEST_CASE(test_initialization){
     ds::dl_node<int> node{1};
     BOOST_CHECK_EQUAL(node.data,1);
     BOOST_CHECK_EQUAL(node.previous, nullptr);
     BOOST_CHECK_EQUAL(node.next, nullptr);
}
BOOST_AUTO_TEST_CASE(test_move_constructor){
     ds::dl_node<int> prev{0};
     ds::dl_node<int> next{1};
     ds::dl_node<int> node{2};
     node.attach_previous(&prev);
     node.attach_next(&next);
     
     ds::dl_node<int> node2{std::move(node)};
     BOOST_CHECK(node2.data == 2);
     BOOST_CHECK(node2.previous->data == prev.data);
     BOOST_CHECK(node2.next->data == next.data);
     BOOST_CHECK(node.previous == nullptr);
     BOOST_CHECK(node.next == nullptr);
}
BOOST_AUTO_TEST_CASE(test_attach_previous_valid){
     ds::dl_node<int> prev{0};
     ds::dl_node<int> node{1};
     node.attach_previous(&prev);
     BOOST_CHECK_EQUAL(node.previous->data, prev.data);
     BOOST_CHECK_EQUAL(prev.next->data, node.data);
}
BOOST_AUTO_TEST_CASE(test_attach_previous_nullptr){
     ds::dl_node<int> node{1};
     node.attach_previous(nullptr);
     BOOST_CHECK_EQUAL(node.previous, nullptr);
}
BOOST_AUTO_TEST_CASE(test_attach_next_valid){
     ds::dl_node<int> next{2};
     ds::dl_node<int> node{1};
     node.attach_next(&next);
     BOOST_CHECK_EQUAL(node.next->data, next.data);
     BOOST_CHECK_EQUAL(next.previous->data, node.data);
}
BOOST_AUTO_TEST_CASE(test_attach_next_nullptr){
     ds::dl_node<int> node{1};
     node.attach_next(nullptr);
     BOOST_CHECK_EQUAL(node.next, nullptr);
}

BOOST_AUTO_TEST_SUITE_END()