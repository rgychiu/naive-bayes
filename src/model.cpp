//
// Created by Roy Chiu on 3/11/18.
//
#include "../header/model.h"

#include <fstream>
#include <cmath>

using namespace std;

// File to read and write to will have all probabilities and confusion matrix

void Model::SaveToFile(string file_name) {
    // Open the new file and write description of data ordering
    ofstream output_file;
    output_file.open(file_name);

    // Write probability data to file
    for (const auto &key_val : train_feature_prob) {
        for (const auto &probability : key_val.second) {
            output_file << 0 << to_string(key_val.first) << " " << to_string(probability) << endl;
        }
    }

    // Write class probability data to file
    for (const auto &key_val : train_class_prob) {
        output_file << 1 << to_string(key_val.first) << " " << to_string(key_val.second) << endl;
    }

    output_file << 2 << endl << to_string(k_value);
    output_file.close();
}

void Model::LoadFromFile(string file_name) {
    ifstream input_file(file_name);
    if (!input_file.is_open()) {
        cout << "Bad file path, cannot open file." << endl;
        return;
    }

    while (!input_file.fail()) {
        int value_code;
        int map_key;
        double value;
        input_file >> value_code >> map_key >> value;
        switch (value_code) {
            case 0:
                train_feature_prob[map_key].push_back(value);
                break;
            case 1:
                train_class_prob[map_key] += value;
                break;
            case 2:
                k_value = map_key;
            default:
                break;
        }
    }
}

void Model::TrainModel(const string &image_path, const string &label_path) {
    training_data.ReadFromImageFile(image_path);
    training_data.ReadFromLabelFile(label_path);
    TrainProb(training_data.GetImages());
    TrainClassProb(training_data.GetLabels());
}

vector<vector<double>> Model::TestModel(const string &test_image_path, const string &test_label_path) {
    // Initialize 10x10 matrix for confusion matrix
    vector<vector<double>> confusion_matrix(10, vector<double>(10, 0));
    test_data.ReadFromImageFile(test_image_path);
    test_data.ReadFromLabelFile(test_label_path);

    vector<Image_Feature> images = test_data.GetImages();
    vector<int> descriptions = test_data.GetLabels();
    for (u_int label_idx = 0; label_idx < descriptions.size(); label_idx++) {
        confusion_matrix.at(descriptions.at(label_idx)).at(Classify(CalculatePostProb(images.at(label_idx))))++;
    }

    for (u_int class_idx = 0; class_idx < confusion_matrix.size(); class_idx++) {
        int total_class_occur = 0;
        for (const auto &label : descriptions) {
            if (label == class_idx) {
                total_class_occur++;
            }
        }

        for (auto &totals : confusion_matrix.at(class_idx)) {
            totals /= total_class_occur;
        }
    }

    return confusion_matrix;
}

vector<string> Model::ProbabilityExtremes(u_int number) {
    u_int highest_idx = 0;
    u_int lowest_idx = 0;
    double running_high = 0;
    double running_low = numeric_limits<double>::max();

    vector<int> descriptions = test_data.GetLabels();
    vector<Image_Feature> images = test_data.GetImages();
    for (u_int desc_idx = 0; desc_idx < descriptions.size(); desc_idx++) {
        if (descriptions.at(desc_idx) == number) {
            map<int, double> post_probability = CalculatePostProb(images.at(desc_idx));

            if (-post_probability.at(number) > running_high) {
                running_high = post_probability.at(number);
                highest_idx = desc_idx;
            }

            if (-post_probability.at(number) < running_low) {
                running_low = post_probability.at(number);
                lowest_idx = desc_idx;
            }
        }
    }

    vector<string> edge_images;
    // Highest value is the smallest probability after negating and vice versa - highest is worse, smaller is better
    edge_images.push_back(images.at(highest_idx).GetImage());
    edge_images.push_back(images.at(lowest_idx).GetImage());
    return edge_images;
}

int Model::Classify(map<int, double> prob_dist) {
    // Sort one element of the hashmap using lambda functions to get highest probability and return key
    vector<pair<int, double>> num_prob;
    for (const auto &mappings : prob_dist) {
        num_prob.emplace_back(mappings);
    }

    partial_sort(num_prob.begin(), num_prob.begin() + 1, num_prob.end(),
                 [](const std::pair<int, double> &prev, const std::pair<int, double> &curr) {
                    return prev.second > curr.second;
                 });

    return num_prob.at(0).first;
}

void Model::TrainProb(vector<Image_Feature> images) {
    // For loop that handles all possible numbers to calculate probabilities for
    for (int num = 0; num < 10; num++) {
        // Keep track of # occurrences for number as well as mapping of feature and total times it's true
        int occur_count = 0;
        map<int, int> feature_occur_ct;
        // Find all occurrences of number in the labels and feature maps of images
        for (u_int label_idx = 0; label_idx < training_data.GetLabels().size(); label_idx++) {
            if (training_data.GetLabels().at(label_idx) == num) {
                // Once match is found, increment occurrence of class and loop through entire feature map
                // Update map of position and # times true
                occur_count++;
                vector<bool> feature_map = images.at(label_idx).GetFeatureMap();
                for (u_int feature_idx = 0; feature_idx < feature_map.size(); feature_idx++) {
                    if (feature_map.at(feature_idx)) {
                        feature_occur_ct[feature_idx]++;
                    } else {
                        // Attempts to insert but will not change value if position already exists
                        // Will still add position even if position is never true
                        feature_occur_ct.insert(make_pair(feature_idx, 0));
                    }
                }
            }
        }

        vector<double> pos_probabilities;
        pos_probabilities.reserve(784);
        for (const auto &pos_occur : feature_occur_ct) {
            // Calculate probability of true for each position and add to map
            pos_probabilities.push_back((k_value + pos_occur.second) / (2 * k_value + occur_count));
        }
        train_feature_prob.insert(make_pair(num, pos_probabilities));
    }
}

void Model::TrainClassProb(vector<int> descriptions) {
    // Count number of occurrences for each class and divide by total examples
    for (int num = 0; num < 10; num++) {
        double occur_count = 0;
        for (const auto &label : descriptions) {
            if (label == num) {
                occur_count++;
            }
        }

        train_class_prob.insert(make_pair(num, occur_count / descriptions.size()));
    }
}

map<int, double> Model::CalculatePostProb(Image_Feature image) {
    map <int, double> post_probabilities;

    // Initialize all values to respective class probabilities
    for (int i = 0; i < 10; i++) {
        post_probabilities[i] += log(train_class_prob.at(i));
    }

    for (u_int feature_idx = 0; feature_idx < image.GetFeatureMap().size(); feature_idx++) {
        if (image.GetPosFeature(feature_idx)) {
            for (const auto &class_feature_prob : train_feature_prob) {
                post_probabilities.at(class_feature_prob.first) += log(class_feature_prob.second.at(feature_idx));
            }
        }
    }

    return post_probabilities;
}

map<int, vector<double>> Model::GetTrainProb() {
    return train_feature_prob;
}

map<int, double> Model::GetClassProb() {
    return train_class_prob;
}