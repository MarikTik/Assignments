#include <boost/test/unit_test.hpp>
#include "linked_list.hpp"

BOOST_AUTO_TEST_SUITE(LINKED_LIST_TEST)


BOOST_AUTO_TEST_CASE(test_initialization){
     ds::linked_list<int> list;
     BOOST_CHECK(list.empty());
}

BOOST_AUTO_TEST_CASE(test_empty_destructor){
     ds::linked_list<int> list;
     class T{};
     ds::linked_list<T> list2;
}

BOOST_AUTO_TEST_CASE(test_list_move_constructor){
     ds::linked_list<int> list;
     list.push_back(1);
     list.push_back(2);
     list.push_back(3);
     ds::linked_list<int> list2{std::move(list)};
     BOOST_CHECK(list.empty());
     auto it = list2.begin();
     BOOST_CHECK_EQUAL(*it, 1);
     BOOST_CHECK_EQUAL(*(++it), 2);
     BOOST_CHECK_EQUAL(*(++it), 3);
     BOOST_CHECK(++it == list2.end());
}

BOOST_AUTO_TEST_CASE(test_list_move_assignment){
     ds::linked_list<int> list;
     list.push_back(1);
     list.push_back(2);
     list.push_back(3);
     ds::linked_list<int> list2;
     list2 = std::move(list);
     BOOST_CHECK(list.empty());
     auto it = list2.begin();
     BOOST_CHECK_EQUAL(*it, 1);
     BOOST_CHECK_EQUAL(*(++it), 2);
     BOOST_CHECK_EQUAL(*(++it), 3);
     BOOST_CHECK(++it == list2.end());
}

BOOST_AUTO_TEST_CASE(test_push_back_single){
     ds::linked_list<int> list;
     list.push_back(1);
     BOOST_CHECK(not list.empty());
     auto it = list.begin();
     BOOST_CHECK_EQUAL(*it, 1);
     BOOST_CHECK(++it == list.end());
}

BOOST_AUTO_TEST_CASE(test_push_front_single){
     ds::linked_list<int> list;
     list.push_front(1);
     BOOST_CHECK(not list.empty());
     auto it = list.begin();
     BOOST_CHECK_EQUAL(*it, 1);
     BOOST_CHECK(++it == list.end());
}

BOOST_AUTO_TEST_CASE(test_push_back_multiple){
     ds::linked_list<int> list;
     list.push_back(1);
     list.push_back(2);
     list.push_back(3);
     BOOST_CHECK(not list.empty());
     auto it = list.begin();
     BOOST_CHECK_EQUAL(*it, 1);
     BOOST_CHECK_EQUAL(*(++it), 2);
     BOOST_CHECK_EQUAL(*(++it), 3);
     BOOST_CHECK(++it == list.end());
}

BOOST_AUTO_TEST_CASE(test_push_front_multiple){
     ds::linked_list<int> list;
     list.push_front(1);
     list.push_front(2);
     list.push_front(3);
     BOOST_CHECK(not list.empty());
     auto it = list.begin();
     BOOST_CHECK_EQUAL(*it, 3);
     BOOST_CHECK_EQUAL(*(++it), 2);
     BOOST_CHECK_EQUAL(*(++it), 1);
     BOOST_CHECK(++it == list.end());
}

BOOST_AUTO_TEST_CASE(test_push_from_both_sides){
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

BOOST_AUTO_TEST_CASE(test_clear){
     ds::linked_list<int> list;
     list.push_front(1);
     list.push_back(2);
     list.push_front(3);
     list.push_back(4);
     list.clear();
     BOOST_CHECK(list.empty());
}

BOOST_AUTO_TEST_CASE(test_remove_in_single_list){
     ds::linked_list<int> list;
     list.push_front(1);
     list.remove([](int val) noexcept{return val == 1;});
     BOOST_CHECK(list.empty());
}

BOOST_AUTO_TEST_CASE(test_remove_in_single_list_with_consecutive_addition){
     ds::linked_list<int> list;
     list.push_front(1);  
     list.remove([](int val) noexcept {return val == 1;});
     list.push_back(2);
     list.remove([](int val) noexcept {return val == 2;});
     BOOST_CHECK(list.empty());
     BOOST_CHECK(list.begin() == list.end());
}

BOOST_AUTO_TEST_CASE(test_remove_in_single_list_with_consecutive_addition_and_removal){
     ds::linked_list<int> list;
     list.push_front(1);  
     list.remove([](int val) noexcept {return val == 1;});
     list.push_back(2);
     list.remove([](int val) noexcept {return val == 2;});
     list.push_front(3);
     list.remove([](int val) noexcept {return val == 3;});
     BOOST_CHECK(list.empty());
     BOOST_CHECK(list.begin() == list.end());
}

BOOST_AUTO_TEST_CASE(test_iterator_with_multiple_occurence_removal){
     ds::linked_list<int> list;
     list.push_back(1);
     list.push_back(2);
     list.push_back(3);
     list.push_back(1);
     list.push_back(2);
     list.push_back(3);
     list.push_back(1);
     list.push_back(1);
     list.push_back(1);
     list.push_back(3);
     list.remove([](int val) noexcept {return val == 1;}, 0);
     auto it = list.begin();
     BOOST_CHECK_EQUAL(*it, 2);
     BOOST_CHECK_EQUAL(*(++it), 3);
     BOOST_CHECK_EQUAL(*(++it), 2);
     BOOST_CHECK_EQUAL(*(++it), 3);
     BOOST_CHECK_EQUAL(*(++it), 3);
     BOOST_CHECK(++it == list.end());
}

BOOST_AUTO_TEST_SUITE_END()


 
 