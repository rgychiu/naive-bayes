//
// Created by Roy Chiu on 3/11/18.
//
#include "../header/model.h"

using namespace std;

int main() {
    int option;
    string image_file;
    string label_file;
    string target_file;
    cout << "Provide path to image file to train from: " << endl;
    cin >> image_file;

    cout << "Provide path to label file to train from: " << endl;
    cin >> label_file;

    auto *model = new Model;
    model->TrainModel(image_file, label_file);

    cout << "Model Trained. Save (0) this model, or load (1) another model?" << endl;
    cin >> option;
    switch (option) {
        case 0:
            cout << "Provide file path to save to." << endl;
            cin >> target_file;
            model->SaveToFile(target_file);
            break;
        case 1:
            cout << "Provide file path to load from." << endl;
            cin >> target_file;
            model->LoadFromFile(target_file);
            break;
        default:
            cout << "Invalid command";
            break;
    }

    cout << "Provide path to image file to test on: " << endl;
    cin >> image_file;

    cout << "Provide path to label file to test on: " << endl;
    cin >> label_file;


    vector<vector<double>> results = model->TestModel(image_file, label_file);
    for (const auto &row : results) {
        for (const auto &percentage : row) {
            cout.precision(2);
            cout << percentage << " ";
        }
        cout << endl;
    }

    for (u_int i = 0; i < 10; i ++) {
        for (const auto &image_strings : model->ProbabilityExtremes(i)) {
            cout << image_strings << endl << "-------------------------------------------------------" << endl;
        }
    }

    delete model;

    return 0;
}
