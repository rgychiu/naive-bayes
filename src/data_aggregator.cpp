//
// Created by Roy Chiu on 3/11/18.
//

#include "../header/data_aggregator.h"

using namespace std;

void Data_Aggregator::ReadFromImageFile(string file_path) {
    // Should exit function on bad file path (check with .isopen)

}

void Data_Aggregator::ReadFromLabelFile(string file_path) {

}

vector<Image_Feature> Data_Aggregator::GetImages() {
    return images;
}

vector<int> Data_Aggregator::GetLabels() {
    return labels;
}