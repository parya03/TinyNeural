/**
 * Stuff for the whole neural network
*/

#include <iostream>
#include "layer.h"

// Training set: contains array of inputs and array of expected outputs
typedef struct {
    double *input;
    double *output;
} training_set_t;

class NeuralNetwork {
    public:
        NeuralNetwork(Layer *layers[], uint32_t numlayers);
        void setInput(double inputs[]); // Set activation of all input nodes to values from array given
        double *calcOutput();
        double calcTotalError();
    private:
        Layer **layers; // Array of pointer to layers
        uint32_t num_layers;
        double total_error; // Total error of network
        double **training_data;
};