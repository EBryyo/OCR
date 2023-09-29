#include "layer.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void free_layer (Layer layer)
{
    for(size_t i = 0; i < layer.w; i++)
    {
        free(layer.weights[i]);
    }
    free(layer.weights);
    free(layer.biases);
}


void sigmoid(double* input)
{
    return;
}


void compute_output(Layer layer, double* input, double* output)
{
    size_t w, h;
    w = layer.w;
    h = layer.h;

    for(size_t i = 0; i < w; i++)
    {
        output[i] = 0;
        for(size_t j = 0; j < h; j++)
        {
            output[i] += (input[j] * layer.weights[i][j]);
        }
        output[i] += layer.biases[i];
    }
    sigmoid(output);
}
