//
// Created by Roy Chiu on 3/11/18.
//
#include "../header/image_features.h"
#include "../header/catch.hpp"

#include <string>

#include CATCH_CONFIG_MAIN

// ---------------------------------------- Test feature map creation --------------------------------------------
// Test cases will also cover both getters
TEST_CASE("Valid string test") {
    auto *test_feature = new Image_Feature;
    string test_string = "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n";
    test_feature->CreateFeatureMap(test_string);

    CHECK(test_feature->GetFeatureMap().size() == 224);
}

TEST_CASE("Valid string background value replacement") {
    auto *test_feature = new Image_Feature;
    string test_string = "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n";
    test_feature->CreateFeatureMap(test_string);

    CHECK(!test_feature->GetPosFeature(0));
}

TEST_CASE("Valid string all background") {
    auto *test_feature = new Image_Feature;
    string test_string = "++++++++++++++++++++++++++++\n"
                         "++++++++++++++++++++++++++++\n"
                         "++++++++++++++++++++++++++++\n"
                         "++++++++++++++++++++++++++++\n"
                         "++++++++++++++++++++++++++++\n"
                         "++++++++++++++++++++++++++++\n"
                         "++++++++++++++++++++++++++++\n"
                         "++++++++++++++++++++++++++++\n";
    test_feature->CreateFeatureMap(test_string);

    CHECK(test_feature->GetFeatureMap().size() == 224);
}

TEST_CASE("Valid string foreground value replacement") {
    auto *test_feature = new Image_Feature;
    string test_string = "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n";
    test_feature->CreateFeatureMap(test_string);

    CHECK(test_feature->GetPosFeature(10));
    CHECK(test_feature->GetPosFeature(11));
    CHECK(test_feature->GetPosFeature(38));
    CHECK(test_feature->GetPosFeature(39));
}

TEST_CASE("Valid string empty background") {
    auto *test_feature = new Image_Feature;
    string test_string = "          ########          \n"
                         "          ########          \n"
                         "          ########          \n"
                         "          ########          \n"
                         "          ########          \n"
                         "          ########          \n"
                         "          ########          \n"
                         "          ########          \n";
    test_feature->CreateFeatureMap(test_string);

    CHECK(!test_feature->GetPosFeature(0));
    CHECK(!test_feature->GetPosFeature(28));
}

TEST_CASE("Empty string") {
    auto *test_feature = new Image_Feature;
    string test_string;
    test_feature->CreateFeatureMap(test_string);

    CHECK(test_feature->GetFeatureMap().empty());
}