//
// Created by Roy Chiu on 3/11/18.
//
#include "data_manager.h"

#include <iostream>
#include <map>

#ifndef NAIVEBAYES_RGYCHIU_MODEL_H
#define NAIVEBAYES_RGYCHIU_MODEL_H

class Model {
public:
    /**
     * Method to save model to file.
     */
    void SaveToFile();

    /**
     * Method to load model from file.
     */
    void LoadFromFile();

    /**
     * Method that trains the model from data provided.
     */
    void TrainModel();

    /**
     * Method to classify all test images.
     * @param test_images all images from test file
     * @return confusion matrix
     */
    vector<double> TestModel(vector<Image_Feature> test_images);
private:
    Data_Manager training_stats;
    Data_Manager test_stats;
    std::map<int, double> probabilities;
    const int kKValue;

    /**
     * Helper method to classify single image.
     * @param image image read from file
     * @return resulting number from classification
     */
    int Classify(Image_Feature image);
};


#endif //NAIVEBAYES_RGYCHIU_MODEL_H
