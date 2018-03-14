//
// Created by Roy Chiu on 3/11/18.
//

#include "../header/image_features.h"

void Image_Feature::CreateFeatureMap(string file_data) {
    for (const auto &value : file_data) {
        feature_map.push_back(value == '#' || value == '+');
    }
}

void Image_Feature::StoreImage(string file_data) {
    int char_counter = 0;
    for (const auto &character : file_data) {
        if (char_counter == Image_Feature::kLine_Length + 1) {
            char_counter = 1;
            image += character;
        } else {
            char_counter++;
            image += character;
        }
    }
}

bool Image_Feature::GetPosFeature(u_int pos) {
    return feature_map.at(pos);
}

string Image_Feature::GetImage() {
    return image;
}

vector<bool> Image_Feature::GetFeatureMap() {
    return feature_map;
}