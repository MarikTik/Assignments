cmake_minimum_required(VERSION 3.22.1)

project(project4)

set(CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED ON)

add_compile_options(
-Wall
-Wextra
-Werror
-pedantic
-Wconversion
-Wsign-conversion
-Wuninitialized
-Wunused
# -Wshadow
-Wformat
-Wmissing-field-initializers
-Wlogical-op
-Wnull-dereference
-Warray-bounds
)

add_executable(a main.cpp DeliveryOrder.cpp BobaOrder.cpp FoodOrder.cpp Account.cpp)


