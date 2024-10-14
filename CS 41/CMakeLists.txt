cmake_minimum_required(VERSION 3.22.1)
project(proj_tester)

add_subdirectory(week13/chaining)

add_executable(${PROJECT_NAME} test.cpp)
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
