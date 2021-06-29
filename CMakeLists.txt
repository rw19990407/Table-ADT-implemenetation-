cmake_minimum_required(VERSION 3.9...3.19)
project(Project5 CXX)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# build test driver executable
add_executable(unit_tests catch.hpp unit_tests.cpp
  abstract_table.hpp
  abstract_list.hpp abstract_iterator.hpp
  test_array_list.cpp array_list.hpp array_list.tpp
  test_linked_list.cpp linked_list.hpp linked_list.tpp
  test_iterators.cpp
  test_table.cpp table.hpp table.tpp)

# enable testing
enable_testing()

# register Catch tests with cmake
include(Catch)
catch_discover_tests(unit_tests)
