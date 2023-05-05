/**
 * Layer class
*/

#include "layer.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "math_funcs.h"

/**
 * Layer class
*/

Layer::Layer(int node_num, double *weight_array, double *bias_array) {
    this->numNodes = node_num;
    this->weights = weight_array;
    this->biases = bias_array;
    this->activation_values = new double[node_num];
}

Layer::Layer(int node_num, Layer *prev, bool isInput) {

    // Allocate arrays and set variables
    this->prev_layer = prev;
    this->numNodes = node_num;
    this->weights = isInput ? NULL : new double[node_num * (prev->numNodes)];
    this->biases = new double[node_num];
    this->activation_values = new double[node_num];
    this->prev_activation_values = (isInput ? NULL : prev->activation_values);
    this->isInput = isInput;
    this->errors = new double[node_num];

    // Randomize weights and biases
    std::srand(time(0));
    if(!isInput) {
        for(int i = 0; i < (node_num * (prev->numNodes)); i++) {
            weights[i] = ((double)std::rand())/RAND_MAX;
        }
        for(int i = 0; i < (node_num); i++) {
            biases[i] = ((double)std::rand())/RAND_MAX;
        }
    }
}

// Calculate the neuron values of this layer
void Layer::calcValues() {
    if(this->isInput) return; // Can't do calculation if this is input node (you set the value, no previous nodes)
    // Multiply the weights matrix with previous layer's activation values
    multiplyMatrices(this->weights, this->prev_layer->numNodes, this->numNodes, prev_activation_values, 1, this->activation_values);

    // Add the biases of each node
    addMatrices(this->activation_values, this->biases, this->numNodes, this->activation_values);

    // Take the ReLU of each value
    reluMatrix(this->activation_values, this->activation_values, this->numNodes);
}