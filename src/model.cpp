//
// Created by Roy Chiu on 3/11/18.
//
#include "../header/model.h"

using namespace std;

// File to read and write to will have all probabilities and confusion matrix

void Model::SaveToFile(string file_name) {

}

void Model::LoadFromFile(string file_name) {

}

void Model::TrainModel(string image_path, string label_path) {

}

vector<double> Model::TestModel(vector<Image_Feature> test_images) {

}

int Model::Classify(Image_Feature image) {

}

void Model::TrainProb(vector<Image_Feature> images) {

}

void Model::TrainClassProb(vector<int> descriptions) {

}

map<int, vector<double>> Model::GetTrainProb() {
    return train_prob;
}

map<int, double> Model::GetClassProb() {
    return train_class_prob;
}