//
// Created by Roy Chiu on 3/11/18.
//
#include "data_aggregator.h"

#include <map>

#ifndef NAIVEBAYES_RGYCHIU_MODEL_H

#define NAIVEBAYES_RGYCHIU_MODEL_H

using namespace std;

class Model {
public:
    /**
     * Method to save model to file.
     * @param file_name name of file to save to
     */
    void SaveToFile(string file_name);

    /**
     * Method to load model from file.
     * @param file_name path of file to load from
     */
    void LoadFromFile(string file_name);

    /**
     * Method that trains the model from data provided.
     * @param image_path path to file with training images
     * @param label_path path to file with training labels
     */
    void TrainModel(const string &image_path, const string &label_path);

    /**
     * Method to classify all test images.
     * @param test_image_path file with images to classify
     * @param test_label_path file with descriptions
     * @return confusion matrix
     */
    vector<vector<double>> TestModel(const string &test_image_path, const string &test_label_path);

    /**
     * Method that finds the images with probability extremes for a given class.
     * No need to test function, finding probabilities same as classify method, except return max value
     * @param number class to find image for
     * @return map of highest and lowest probability in test files
     */
    vector<string> ProbabilityExtremes(u_int number);

    map<int, vector<double>> GetTrainProb();
    map<int, double> GetClassProb();
private:
    Data_Aggregator training_data;
    Data_Aggregator test_data;
    map<int, vector<double>> train_feature_prob;
    map<int, double> train_class_prob;
    double k_value = 0.1;

    /**
     * Helper method to classify single image.
     * @param prob_dist posterior probabilities
     * @return resulting number from classification
     */
    int Classify(map<int, double> prob_dist);

    /**
     * Helper method to calculate probabilities for each position.
     * @param image image read from file
     * @return distribution of probabilities
     */
    map<int, double> CalculatePostProb(Image_Feature image);

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
