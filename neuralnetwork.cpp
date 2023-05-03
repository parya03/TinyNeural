/**
 * Contains neural network stuff
*/

#include <iostream>
#include "neuralnetwork.h"
#include "layer.h"

Layer input(2, NULL, true); // 0 previous node neurons because no previous node
Layer h1(2, &input, false);
Layer h2(2, &h1, false);
Layer output(1, &h2, false);

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

double NeuralNetwork::calcTotalError() {
    
}