cmake_minimum_required(VERSION 3.5)
project(naivebayes-rgychiu)

set(CMAKE_CXX_STANDARD 14)

add_executable(naivebayes src/classifier_main.cpp)
add_executable(unit-tests test/model_test.cpp)
