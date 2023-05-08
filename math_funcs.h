#ifndef MATH_FUNCS_H
#define MATH_FUNCS_H

#include <iostream>

double relu(double x);
void map(double a[], double b[], uint32_t a_b_size, double func(double in));
void reluMatrix(double a[], double b[], uint32_t a_b_size);
void multiplyMatrices(
        double a[],
        const uint32_t a_rows,
        const uint32_t a_cols,
        double b[],
        const uint32_t b_cols,
        double c[]);
void addMatrices(double a[], double b[], uint32_t a_b_size, double c[]);
void matrixTranspose(double *matrix_in, uint32_t matrix_rows, uint32_t matrix_cols, double* matrix_out);

#endif