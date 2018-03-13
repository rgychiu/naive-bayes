cmake_minimum_required(VERSION 3.5)
project(naivebayes-rgychiu)

set(CMAKE_CXX_STANDARD 14)

add_executable(naivebayes src/classifier_main.cpp src/data_aggregator.cpp src/image_features.cpp src/model.cpp)
add_executable(unit-tests test/model_test.cpp test/data_aggregator_test.cpp test/image_features_test.cpp
        src/model.cpp src/data_aggregator.cpp src/image_features.cpp)
