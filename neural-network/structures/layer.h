#include <stddef.h>

#ifndef LAYER_H
#define LAYER_H

typedef struct Layer
{
    size_t w; //width of matrix, number of sigmoids
    size_t h; //height of matrix, number of inputs/weights
    double** weights;
    double* biases;
}Layer;

void free_layer(Layer layer);
//frees memory allocated to the weights and biases of layer

void compute_output(Layer layer, double* input, double* output);
//computes the outputs of the layer for given inputs into output
// /!\ allocate memory for output with calloc(layer.w, sizeof(double))

#endif
