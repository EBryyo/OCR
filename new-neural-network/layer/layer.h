#ifndef LAYER_H
#define LAYER_H

#include <stddef.h>

typedef struct {
    size_t w; //width of the layer - number of neurons
    size_t h; //height of the layer - number of parent neurons
    double *biases; //biases of each neuron - len = w
    double **weights; //weights of each neuron - len = w
} Layer;

double* activation(double* input, size_t len);

#endif
