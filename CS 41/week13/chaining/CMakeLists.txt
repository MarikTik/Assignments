cmake_minimum_required(VERSION 3.22.1)

project(ds_tester)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

include_directories(${SRC_DIR})

file(GLOB TEST_FILES ${TEST_DIR}/*.cpp)

message(STATUS "TESTING: ${TEST_FILES}")
add_executable(${PROJECT_NAME} ${TEST_FILES})

target_link_libraries(${PROJECT_NAME} Boost::unit_test_framework)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
# target_precompile_headers(${PROJECT_NAME} PRIVATE <boost/test/unit_test.hpp>)
target_compile_options(${PROJECT_NAME} PRIVATE 
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Wcast-align
    -Wunused
    -Woverloaded-virtual
    -Wconversion
    -Wsign-conversion
    -Wduplicated-cond
    -Wduplicated-branches
    -Wlogical-op
    -Wnull-dereference
    -Wuseless-cast
    -Wdouble-promotion
    -Wformat=2
    -Wmissing-include-dirs
    -Wstrict-overflow
    -Wundef
    -Wredundant-decls
    -Wcast-qual
    -Wswitch-default
    -Wswitch-enum
    -Wswitch
    -Winline
    -Wdisabled-optimization
    -Wmissing-noreturn
    -Wnoexcept
    -Woverlength-strings
    -Wshift-overflow
    -Wstrict-null-sentinel
    -Wstack-protector
    -Wstrict-aliasing
    -Wwrite-strings
    -Wunsafe-loop-optimizations
    -Wvariadic-macros
    -Wvla
    -Wmissing-declarations
    -Wreturn-type
    -Wmissing-format-attribute
    -Wlarger-than=8192
)

enable_testing()

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
