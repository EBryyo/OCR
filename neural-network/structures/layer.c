#include "layer.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void free_layer (Layer layer)
{
    if (!layer.passive)
    {
        for(size_t i = 0; i < layer.w; i++)
        {
            free(layer.weights[i]);
        }
        free(layer.weights);
        free(layer.biases);
    }
}


void sigmoid(double* input, size_t len)
{
    //applies sigmoid function in place to input array 
    for(size_t i = 0; i < len; i++)
    {
        //printf("%3g  ", input[i]);
        //printf("%3g\n", 1 / (1 + exp(-input[i])));
        input[i] = 1 / (1 + exp(-input[i]));
        //input[i] = (input[i] > 0.5);
    }
    return;
}


void compute_output(Layer layer, double* input, double* output)
{
    //computes output of neuron layer 
    //with matricial product and sigmoid function
    //sigmoid : f(x) = 1/(1+e^(-x))

    size_t w, h;
    w = layer.w;
    h = layer.h;

    //if layer is passive, the output signal is simply the input signal
    if (layer.passive)
    {
        for(size_t i = 0; i < w; i++)
        {
            output[i] = input[i];
        }
        //sigmoid(output, w);
    }

    //else, apply linear combination of weights and inputs for each neuron
    else
    {
        for(size_t i = 0; i < w; i++)
        {
            output[i] = 0;
            for(size_t j = 0; j < h; j++)
            {
                output[i] += (input[j] * layer.weights[i][j]);
            }
            output[i] += layer.biases[i];
        }
        sigmoid(output, w);
    }
}
