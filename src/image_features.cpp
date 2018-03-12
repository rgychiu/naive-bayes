//
// Created by Roy Chiu on 3/11/18.
//

#include "../header/image_features.h"

void Image_Feature::CreateFeatureMap(string file_data) {
    for (const auto &value : file_data) {
        feature_map.push_back(value == '#' || value == '+');
    }
}

bool Image_Feature::GetPosFeature(u_int pos) {
    return feature_map.at(pos);
}

vector<bool> Image_Feature::GetFeatureMap() {
    return feature_map;
}