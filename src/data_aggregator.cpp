//
// Created by Roy Chiu on 3/11/18.
//
#include "../header/data_aggregator.h"

#include <fstream>

using namespace std;

void Data_Aggregator::ReadFromImageFile(string file_path) {
    // Should exit function on bad file path (check with .isopen)
    ifstream input_file(file_path);
    if (!input_file.is_open()) {
        cout << "Bad file path, unable to open file." << endl;
        return;
    }

    string line;
    string image_text;
    int line_count = 0;
    while (getline(input_file, line)) {
        if (line_count == 28) {
            auto *new_image = new Image_Feature;
            new_image->CreateFeatureMap(image_text);
            new_image->StoreImage(image_text);
            images.push_back(*new_image);
            image_text = line;
            line_count = 1;
        } else {
            image_text += line;
            line_count++;
        }
    }

    // Check if last line read was 28th line
    if (line_count == 28) {
        auto *new_image = new Image_Feature;
        new_image->CreateFeatureMap(image_text);
        new_image->StoreImage(image_text);
        images.push_back(*new_image);
    }
}

void Data_Aggregator::ReadFromLabelFile(string file_path) {
    ifstream input_file(file_path);
    if (!input_file.is_open()) {
        cout << "Bad file path, unable to open file." << endl;
        return;
    }

    int label;
    while (input_file >> label) {
        labels.push_back(label);
    }
}

vector<Image_Feature> Data_Aggregator::GetImages() {
    return images;
}

vector<int> Data_Aggregator::GetLabels() {
    return labels;
}