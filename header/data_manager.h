//
// Created by Roy Chiu on 3/11/18.
//
#include "image_features.h"

#include <iostream>

#ifndef NAIVEBAYES_RGYCHIU_DATAMANAGER_H
#define NAIVEBAYES_RGYCHIU_DATAMANAGER_H


class Data_Manager {
public:
    /**
     * Method to read images from file.
     */
    void ReadFromImageFile();

    /**
     * Method to read image descriptions from file.
     */
    void ReadFromLabelFile();

    /**
     * Method to get all images.
     * @return list of all images
     */
    std::vector<Image_Feature> GetImages();

    /**
     * Method to get all image descriptions. Order matches image order.
     * @return list of all image descriptions
     */
    std::vector<int> GetLabels();
private:
    std::vector<Image_Feature> images;
    std::vector<int> labels;
};


#endif //NAIVEBAYES_RGYCHIU_DATAMANAGER_H
