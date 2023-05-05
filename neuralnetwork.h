/**
 * Stuff for the whole neural network
*/

#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <iostream>
#include "layer.h"

// Training set: contains array of inputs and array of expected outputs
typedef struct {
    double *input;
    double *output;
} training_set_t;

// Contains array of pointers to training sets, and number of sets
typedef struct {
    training_set_t **data;
    uint32_t sets;
} training_data_t;

class NeuralNetwork {
    public:
        NeuralNetwork(Layer *layers[], uint32_t numlayers);
        void setInput(double inputs[]); // Set activation of all input nodes to values from array given
        double* calcOutput();
        double calcTotalError(training_set_t *set); // Calculate total error for one training set
        double calcAverageTotalError(training_data_t *data); // Calculate average error for all training data in array
    private:
        Layer **layers; // Array of pointer to layers
        uint32_t num_layers;
        double average_total_error; // Average total error of network
        training_set_t *training_data; // Array of training data
        void setPrevLayerErrors(uint32_t layer_index); // Set error matrices for all layers
};

#endif