project(borg_tester)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR})
find_package(Boost REQUIRED COMPONENTS unit_test_framework)
include_directories(${SRC_DIR})
include_directories(${SRC_DIR}/collections)
include_directories(${SRC_DIR}/parser)
include_directories(${SRC_DIR}/utils)
include_directories(${SRC_DIR}/interpreter)
include_directories(${SRC_DIR}/interpreter/expressions)

file(GLOB TEST_FILES ${TEST_DIR}/collections/*.cpp)

# message(STATUS "TESTING: ${TEST_FILES}")
add_executable(${PROJECT_NAME} ${TEST_FILES})

target_link_libraries(${PROJECT_NAME} Boost::unit_test_framework)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)