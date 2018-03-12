//
// Created by Roy Chiu on 3/11/18.
//
#include "../header/catch.hpp"
#include "../header/model.h"

#define CATCH_CONFIG_MAIN

// ------------------------------------------- Test file read and write ---------------------------------------------
// Both save and load from file tested simultaneously
// If file can be saved and then loaded successfully, both methods work
// No good way to test for file existence
// Emphasis on loading testing - save can put anything into a file as long as file created
TEST_CASE("Valid save and load") {

}

TEST_CASE("Valid save invalid load path") {

}

TEST_CASE("Valid load bad data") {

}

// ---------------------------------------------- Test train model --------------------------------------------------
// Utilizes helper probability calculation methods - test both
TEST_CASE("Valid train model") {

}

TEST_CASE("Invalid train bad image data") {

}

TEST_CASE("Invalid train bad class data") {

}

//Unable to test classification method - based on probabilities and training data