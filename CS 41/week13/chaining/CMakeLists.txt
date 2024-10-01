cmake_minimum_required(VERSION 3.22.1)

project(ds_tester)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

include_directories(${SRC_DIR})

file(GLOB TEST_FILES ${TEST_DIR}/*.cpp)
 
add_executable(${PROJECT_NAME} ${TEST_FILES})

#ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK) 

target_link_libraries(${PROJECT_NAME} Boost::unit_test_framework)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
# target_precompile_headers(${PROJECT_NAME} PRIVATE <boost/test/unit_test.hpp>)

enable_testing()
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
