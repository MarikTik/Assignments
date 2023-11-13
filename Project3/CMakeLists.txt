cmake_minimum_required(VERSION 3.22.1)

project(Test LANGUAGES CXX)
set(CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED ON)


set(CMAKE_CXX_COMPILE_FEATURES $(CMAKE_CXX_COMPILE_FEATURES) "
-Wall
-Wextra
-Werror
-pedantic
-Wconversion
-Wsign-conversion
-Wuninitialized
-Wunused
-Wshadow
-Wformat
-Wmissing-field-initializers
-Wlogical-op
-Wnull-dereference
-Warray-bounds
")


# set(HEADER_FILES minion.h)

# add_library(lib header-impl.cpp ${HEADER_FILES})
 
add_executable(a Minion.cpp main.cpp)
# target_include_directories(a PRIVATE "./")

 
 
add_compile_options($(CMAKE_CXX_COMPILE_FEATURES))