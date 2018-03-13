//
// Created by Roy Chiu on 3/11/18.
//
#include "../header/model.h"

using namespace std;

int main() {
    auto *model = new Model;
    model->TrainModel("../data/trainingimages.txt", "../data/traininglabels.txt");

    vector<vector<double>> results = model->TestModel("../data/testimages.txt", "../data/testlabels.txt");
    for (const auto &row : results) {
        for (const auto &percentage : row) {
            cout.precision(2);
            cout << percentage << " ";
        }
        cout << endl;
    }

    for (u_int i = 0; i < 10; i ++) {
        for (const auto &image_strings : model->HighestProbability(i)) {
            cout << image_strings << endl << "-------------------------------------------------------" << endl;
        }
    }

    delete model;

    return 0;
}
