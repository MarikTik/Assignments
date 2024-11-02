set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# add_subdirectory(tests)
project(borg)
add_executable(${PROJECT_NAME} ${SRC_DIR}/main.cpp ${SRC_FILES})


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

include_directories(${SRC_DIR})
include_directories(${SRC_DIR}/collections)
include_directories(${SRC_DIR}/parser)
include_directories(${SRC_DIR}/utils)
include_directories(${SRC_DIR}/interpreter)
include_directories(${SRC_DIR}/interpreter/expressions)

file(
     GLOB SRC_FILES 
    #  ${SRC_DIR}/*.cpp
     ${SRC_DIR}/collections/*.cpp
    #  ${SRC_DIR}/parser/*.cpp
    #  ${SRC_DIR}/utils/*.cpp
    #  ${SRC_DIR}/interpreter/*.cpp
    #  ${SRC_DIR}/interpreter/expressions/*.cpp
)

 


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
