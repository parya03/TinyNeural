#include <iostream>
#include "neuralnetwork.h"
#include "layer.h"

#define LEARNING_RATE 0.3

// Layers for neural network
Layer input(2, NULL, true); // 0 previous node neurons because no previous node
Layer h1(2, &input, false);
// Layer h2(2, &h1, false);
Layer output(1, &h1, false);

// Array of pointers to input to neural network
Layer *layers[] = {&input, &h1, &output};

using namespace std;

int main() {
    // Create instance of neural network
    NeuralNetwork nn(layers, 3);

    // Inputs and outputs to neural network training set
    double inputs[] = {1, 1};
    double outputs[] = {0.0};

    // Example training set
    training_set_t set1 = {inputs, outputs};

    cout << "Error of output with training input: " << nn.calcTotalError(&set1) << "\n";
    for(int i = 0; i < 3; i++) {
        cout << "Errors of layer: " << i << " - [";
        for(int o = 0; o < layers[i]->numNodes; o++) {
            cout << layers[i]->errors[o] << " ";
        }
        cout << "]\n";
    }
    cout << "Output layer value: " << (nn.calcOutput())[0] << "\n";

    return 0;
}