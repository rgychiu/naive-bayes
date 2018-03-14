//
// Created by Roy Chiu on 3/11/18.
//
#include "../header/image_features.h"
#include "../header/catch.hpp"

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

    CHECK(test_feature->GetFeatureMap().size() == 232);
    delete test_feature;
}

TEST_CASE("Valid string background value replacement") {
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
    delete test_feature;
}

TEST_CASE("Valid string all background") {
    auto *test_feature = new Image_Feature;
    string test_string = "                            \n"
                         "                            \n"
                         "                            \n"
                         "                            \n"
                         "                            \n"
                         "                            \n"
                         "                            \n"
                         "                            \n";
    test_feature->CreateFeatureMap(test_string);

    CHECK(test_feature->GetFeatureMap().size() == 232);
    delete test_feature;
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

    CHECK(test_feature->GetPosFeature(1));
    CHECK(test_feature->GetPosFeature(11));
    CHECK(test_feature->GetPosFeature(38));
    CHECK(test_feature->GetPosFeature(39));
    delete test_feature;
}

TEST_CASE("Empty string") {
    auto *test_feature = new Image_Feature;
    string test_string;
    test_feature->CreateFeatureMap(test_string);

    CHECK(test_feature->GetFeatureMap().empty());
    delete test_feature;
}

// ------------------------------------------ Test image to string ----------------------------------------------
TEST_CASE("Valid image return foreground") {
    auto *test_feature = new Image_Feature;
    string test_string = "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n"
                         "++++++++++########++++++++++\n";
    test_feature->StoreImage(test_string);

    CHECK(test_feature->GetImage() == test_string);
    delete test_feature;
}

TEST_CASE("Valid image return whitespace preservation") {
    auto *test_feature = new Image_Feature;
    string test_string = "          ########          \n"
                         "          ########          \n"
                         "          ########          \n"
                         "          ########          \n"
                         "          ########          \n"
                         "          ########          \n"
                         "          ########          \n"
                         "          ########          \n";
    test_feature->StoreImage(test_string);

    CHECK(test_feature->GetImage() == test_string);
    delete test_feature;
}

TEST_CASE("Valid image read all background") {
    auto *test_feature = new Image_Feature;
    string test_string = "                            \n"
                         "                            \n"
                         "                            \n"
                         "                            \n"
                         "                            \n"
                         "                            \n"
                         "                            \n"
                         "                            \n";
    test_feature->StoreImage(test_string);

    CHECK(test_feature->GetImage() == test_string);
    delete test_feature;
}

TEST_CASE("Valid image read single line") {
    auto *test_feature = new Image_Feature;
    string test_string = "                            \n                            \n";
    test_feature->StoreImage(test_string);

    CHECK(test_feature->GetImage() == test_string);
    delete test_feature;
}

TEST_CASE("Empty image") {
    auto *test_feature = new Image_Feature;
    string test_string;
    test_feature->StoreImage(test_string);

    CHECK(test_feature->GetImage().empty());
    delete test_feature;
}