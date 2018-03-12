//
// Created by Roy Chiu on 3/11/18.
//

#include "../header/image_features.h"

void Image_Feature::CreateFeatureMap(string file_data) {
    for (reverse_iterator reverse_string = file_data.rbegin(); reverse_string != file_data.rend(); ++reverse_string) {
        feature_map.push_back(*reverse_string == "#");
    }
}

bool Image_Feature::GetPosFeature(int pos) {
    return feature_map.at(pos);
}

vector<bool> Image_Feature::GetFeatureMap() {
    return feature_map;
}