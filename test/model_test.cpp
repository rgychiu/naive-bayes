//
// Created by Roy Chiu on 3/11/18.
//
#include "../header/model.h"

#define CATCH_CONFIG_MAIN
#include "../header/catch.hpp"

// ------------------------------------------- Test file read and write ---------------------------------------------
// No good way to test for file existence
// Emphasis on loading testing - save can put anything into a file as long as file created, confidence in ouput methods
TEST_CASE("Valid load") {
    auto *test_model = new Model;
    test_model->LoadFromFile("../data/test1.txt");

    CHECK(test_model->GetTrainProb().size() == 10);
    delete test_model;
}

TEST_CASE("Valid save invalid load path") {
    auto *test_model = new Model;
    test_model->TrainModel("../data/testsampleimages.txt", "../data/testsamplelabels.txt");
    test_model->SaveToFile("../data/testwrite.txt");
    test_model->LoadFromFile("../data/test.txt");

    CHECK(test_model->GetTrainProb().size() == 10);
    CHECK(Approx(test_model->GetTrainProb().at(9).at(0)) == 0.0833333333);
    delete test_model;
}

TEST_CASE("Invalid load path") {
    auto *test_model = new Model;
    test_model->LoadFromFile("asdfjklahsd.txt");

    CHECK(test_model->GetClassProb().empty());
    CHECK(test_model->GetTrainProb().empty());
    delete test_model;
}

// ---------------------------------------------- Test train model --------------------------------------------------
// Utilizes helper probability calculation methods - test both
// No need to test probability calculators individually - testing multiplication
// Sample files allow testing edge cases like single training image for a prior
TEST_CASE("Valid train model valid feature probabilities") {
    auto *test_model = new Model;
    test_model->TrainModel("../data/testsampleimages.txt", "../data/testsamplelabels.txt");

    CHECK(test_model->GetTrainProb().size() == 10);
    CHECK(Approx(test_model->GetTrainProb().at(9).at(0)) == 0.0833333333);
    CHECK(Approx(test_model->GetTrainProb().at(9).at(210)) == 0.0833333333);
    delete test_model;
}

TEST_CASE("Valid train model valid prior") {
    auto *test_model = new Model;
    test_model->TrainModel("../data/testsampleimages.txt", "../data/testsamplelabels.txt");

    CHECK(test_model->GetClassProb().size() == 10);
    CHECK(test_model->GetClassProb().at(0) == 0.5);
    delete test_model;
}

// --------------------------------------------- Test classificiation -----------------------------------------------
// Confidence in counting -- test small files for confusion matrix placement and calculation
// Small enough file so that classification will produce expected results
TEST_CASE("Valid classification") {
    auto *test_model = new Model;
    test_model->TrainModel("../data/trainingimages.txt", "../data/traininglabels.txt");

    CHECK(test_model->TestModel("../data/posteriorextreme.txt", "../data/posteriorextremelabels.txt")
                      .at(0).at(0) == 0.5);
    delete test_model;
}

// ------------------------------------------ Test posterior extremes -----------------------------------------------
// Confidence in double comparison -- test small smiles for correct posterior probabilities
// Small enough file to produce expected results
TEST_CASE("Valid extreme comparisons") {
    auto *test_model = new Model;
    test_model->TrainModel("../data/trainingimages.txt", "../data/traininglabels.txt");
    test_model->TestModel("../data/posteriorextreme.txt", "../data/posteriorextremelabels.txt");

    CHECK(test_model->ProbabilityExtremes(9).size() == 2);
    delete test_model;
}