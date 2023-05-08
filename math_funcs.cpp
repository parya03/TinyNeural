#include <iostream>
#include <cmath>
#include "math_funcs.h"

/**
 * Some math functions:
*/

// ReLU activation function
inline double relu(double x) {
    return x > 0 ? x : 0;
}

// Apply function to whole matrix
void map(double a[], double b[], uint32_t a_b_size, double func(double in)) {
    for(uint32_t i = 0; i < a_b_size; i++) {
        b[i] = func(a[i]);
    }
}

// Find ReLU of whole matrix
void reluMatrix(double a[], double b[], uint32_t a_b_size) {
    // for(uint32_t i = 0; i < a_b_size; i++) {
    //     b[i] = relu(a[i]);
    // }
    map(a, b, a_b_size, relu);
}



// Multiply 2 matrices
// TODO: OpenCL
void multiplyMatrices(
        double a[],
        const uint32_t a_rows,
        const uint32_t a_cols,
        double b[],
        const uint32_t b_cols,
        double c[]) {
    // https://en.wikipedia.org/wiki/Row-_and_column-major_order

    int a_size = a_rows * a_cols;
    
    int c_index = 0;
    
    for(int a_current = 0; a_current < a_size; a_current += a_cols) { //Iterate through A row by row
        //For each row, start iterating through columns in B
        for(int b_current = 0; b_current < b_cols; ++b_current) {
            double buffer = 0;
            // Iterate through numbers to multiply together
            for(int i = 0; i < a_cols; ++i) {
                buffer += (a[i + a_current] * b[(i*b_cols) + b_current]);
            }
            c[c_index] = buffer;
            
            ++c_index;
        }
    }
}

// Add matrices
void addMatrices(double a[], double b[], uint32_t a_b_size, double c[]) {
    for(uint32_t i = 0; i < a_b_size; i++) {
        c[i] = a[i] + b[i];
    }
}

// Todo: OpenCL?
void matrixTranspose(double *matrix_in, uint32_t matrix_rows, uint32_t matrix_cols, double* matrix_out) {
    uint32_t count = 0;
    for(uint32_t i = 0; i < matrix_cols; i++) {
        for(uint32_t o = 0; o < matrix_rows; o++) {
            matrix_out[(o*matrix_rows) + matrix_cols] = matrix_in[count];
            count++;
        }
    }
}