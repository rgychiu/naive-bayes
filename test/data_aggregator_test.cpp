//
// Created by Roy Chiu on 3/11/18.
//
#include "../header/data_aggregator.h"
#include "../header/catch.hpp"

// --------------------------------------- Test reading images from file --------------------------------------------
TEST_CASE("Valid image file read") {
    string test_path = "../data/testsampleimages.txt";
    auto *test_aggregator = new Data_Aggregator;
    test_aggregator->ReadFromImageFile(test_path);

    CHECK(test_aggregator->GetImages().size() == 2);
    delete test_aggregator;
}

TEST_CASE("Valid image file read background preserve") {
    string test_path = "../data/testsampleimages.txt";
    auto *test_aggregator = new Data_Aggregator;
    test_aggregator->ReadFromImageFile(test_path);

    CHECK(!test_aggregator->GetImages().at(0).GetPosFeature(0));
    CHECK(!test_aggregator->GetImages().at(0).GetPosFeature(28));
    delete test_aggregator;
}

TEST_CASE("Valid image file read foreground preserve") {
    string test_path = "../data/testsampleimages.txt";
    auto *test_aggregator = new Data_Aggregator;
    test_aggregator->ReadFromImageFile(test_path);

    CHECK(test_aggregator->GetImages().at(0).GetPosFeature(211));
    CHECK(test_aggregator->GetImages().at(0).GetPosFeature(212));
    delete test_aggregator;
}

TEST_CASE("Bad image file path") {
    string test_path = "../data/fasdlkj.txt";
    auto *test_aggregator = new Data_Aggregator;
    test_aggregator->ReadFromImageFile(test_path);

    CHECK(test_aggregator->GetImages().empty());
    delete test_aggregator;
}

// --------------------------------------- Test reading descriptions from file --------------------------------------
// Similar implementation to reading images from file - only test valid cases
TEST_CASE("Valid description file read") {
    string test_path = "../data/testsamplelabels.txt";
    auto *test_aggregator = new Data_Aggregator;
    test_aggregator->ReadFromLabelFile(test_path);

    CHECK(test_aggregator->GetLabels().size() == 2);
    delete test_aggregator;
}