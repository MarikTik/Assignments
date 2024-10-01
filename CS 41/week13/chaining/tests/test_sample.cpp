#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE MyModule
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(MyTestCase)
{
    BOOST_CHECK(1 + 1 == 2);
}

 