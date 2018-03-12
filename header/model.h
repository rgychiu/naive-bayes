//
// Created by Roy Chiu on 3/11/18.
//
#include "data_aggregator.h"

#include <iostream>
#include <map>

#ifndef NAIVEBAYES_RGYCHIU_MODEL_H
#define NAIVEBAYES_RGYCHIU_MODEL_H

using namespace std;

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

    map<int, vector<double>> GetTrainProb();
    map<int, double> GetClassProb();
private:
    Data_Aggregator training_data;
    Data_Aggregator test_data;
    map<int, vector<double>> train_prob;
    map<int, double> train_class_prob;
    map<int, double> probabilities;
    const int kKValue;

    /**
     * Helper method to classify single image.
     * @param image image read from file
     * @return resulting number from classification
     */
    int Classify(Image_Feature image);

    /**
     * Helper method to generate training probabilities based on training set.
     * @param images training set of images
     */
    void TrainProb(vector<Image_Feature> images);

    /**
     * Helper method to estimate priors.
     * @param descriptions training set of priors
     */
    void TrainClassProb(vector<int> descriptions);
};


#endif //NAIVEBAYES_RGYCHIU_MODEL_H
