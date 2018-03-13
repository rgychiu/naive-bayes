//
// Created by Roy Chiu on 3/11/18.
//

#include <iostream>
#include <vector>

#ifndef NAIVEBAYES_RGYCHIU_IMAGE_FEATURES_H

#define NAIVEBAYES_RGYCHIU_IMAGE_FEATURES_H

using namespace std;

class Image_Feature {
public:
    /**
     * Method to generate vector of features from file input.
     * @param file_data string read from file
     */
    void CreateFeatureMap(string file_data);

    /**
     * Method to store string representation of image.
     * @param file_data string read from file.
     */
    void StoreImage(string file_data);

    /**
     * Method to get specific feature.
     * @param pos position to retrieve feature
     * @return feature value at specified position
     */
    bool GetPosFeature(u_int pos);

    /**
     * Method to print the instance image.
     * @return image as string
     */
    string GetImage();

    /**
     * Method that returns the entire feature mapping.
     * @return instance feature map
     */
    vector<bool> GetFeatureMap();
private:
    vector<bool> feature_map;
    string image;
};

#endif //NAIVEBAYES_RGYCHIU_IMAGE_FEATURES_H
