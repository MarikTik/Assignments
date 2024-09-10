cmake_minimum_required(VERSION 3.22.1)
project(proj_tester)

add_executable(${PROJECT_NAME} week15/src/main.cpp)


add_compile_options(
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
    -Wunsuffixed-float-constants
    -Wvariadic-macros
    -Wvla
    -Wweak-vtables
    -Wmissing-declarations
    -Wmissing-prototypes
    -Wreturn-type
    -Wmissing-format-attribute
    -Wlarger-than=8192
    -Wpadded
)
