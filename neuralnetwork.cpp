/**
 * Contains neural network stuff
*/

#include <iostream>
#include "neuralnetwork.h"
#include "layer.h"
#include <cmath>
#include "math_funcs.h"

// Passed in array of pointers to layers (first being input, last being output) and number of layers
NeuralNetwork::NeuralNetwork(Layer *layers_in[], uint32_t numlayers) {
    // double inputvalues[2] = {1, 1};

    // input.activation_values = in;

    // Add layers
    this->layers = new Layer*[numlayers];
    for(int i = 0; i < numlayers; i++) {
        layers[i] = layers_in[i];
    }

    this->num_layers = numlayers;

    // while(1) {
    //     h1.calcValues();
    //     h2.calcValues();
    //     output.calcValues();

    //     for(int i = 0; i < output.numNodes; i++) {
    //         std::cout << output.activation_values[i] << std::endl;
    //     }
    // }
}

double *NeuralNetwork::calcOutput() {
    // Calculate value of each layer, skipping the first one (input layer)
    for(int i = 1; i < this->num_layers; i++) {
        layers[i]->calcValues();
    }

    // Return activation values of last layer
    return layers[num_layers-1]->activation_values;
}

void NeuralNetwork::setInput(double inputs[]) {
    for(int i = 0; i < this->layers[0]->numNodes; i++) {
        this->layers[0]->activation_values[i] = inputs[i];
    }
}

double NeuralNetwork::calcTotalError(training_set_t *set) {
    // Set input to training set provided
    setInput(set->input);

    // Calculate total error on output node by using formula (expected-actual)^2 on all outputs
    double output = 0;
    double *temp = calcOutput();
    for(uint32_t i = 0; i < layers[num_layers - 1]->numNodes; i++) {
        double err = pow((set->output[i] - (layers[num_layers - 1]->activation_values[i])), 2);
        output += err;
        layers[num_layers - 1]->errors[i] = err; // Set error for the node
    }

    setPrevLayerErrors((num_layers - 1));

    return output;
}

double NeuralNetwork::calcAverageTotalError(training_data_t *data) {
    double totalerror = 0;

    for(uint32_t i = 0; i < data->sets; i++) {
        totalerror += calcTotalError(data->data[i]);
    }

    average_total_error = (totalerror / (double)(data->sets));
    return average_total_error;
}

// NOTE: Assumes errors of current layer are set
void NeuralNetwork::setPrevLayerErrors(uint32_t layer_index) {
    // Base case for recursion - doing it below index 1 would lead to setting errors for input - doesn't make sense
    if(layer_index == 1)
        return;

    // Allocate and find transpose of weights matrix for previous layer
    double matrix_transpose[layers[layer_index - 1]->numNodes];
    matrixTranspose(layers[layer_index - 1]->weights, layers[layer_index]->numNodes, layers[layer_index - 1]->numNodes, matrix_transpose);

    // Do matrix multiplication to find errors of previous layer
    multiplyMatrices(matrix_transpose, layers[layer_index - 1]->numNodes, \
    layers[layer_index]->numNodes, layers[layer_index]->errors, 1, layers[layer_index - 1]->errors);

    // Do recursion for all previous layers
    setPrevLayerErrors((layer_index - 1));
}

void NeuralNetwork::train(training_data_t *data) {
    // Prepare
    // double average_total_err = calcAverageTotalError(data);
    // setPrevLayerErrors(this->num_layers);

    // Calculate average output and node errors
    double *average_total_errors = new double[num_layers];

    for(uint32_t i = 0; i < data->sets; i++) {
        average_total_errors[num_layers - 1] += calcTotalError(data->data[i]); // Set error for output node
        setPrevLayerErrors(num_layers);
        for(int i = (num_layers-2); i >= 0; i--) {
            // TODO: Come back to this when not sleepy
        }
    }

    // average_total_error = (totalerror / (double)(data->sets));

}