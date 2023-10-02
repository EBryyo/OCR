#include <stdio.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include "../structures/mlp.h"
#include "../structures/layer.h"


void get_target_array(double* target, int i, size_t len)
{ 
    //fills target array with target values for a given neuron
    //target must be allocated beforehand
    
    target[i] = 0.99;
    for(size_t n = 0; n < len; n++)
    {
        if (n != i)
        {
            target[n] = 0.01;
        }
    }
    printf("target array obtained.\n");
}

double total_error(double* output, double* target, size_t len)
{
    //computes total error of output array according to target array
    
    double err = 0;
    for(size_t i = 0; i < len; i++)
    {
        err += 0.5 * pow((target[i] - output[i]), 2);
    }
    printf("total error computed.\n");
    return err;
}

void gradient_descent(mlp* n, double* target, double* input)
{
    //applies the gradient descent algorithm on MLP n


    //compute outputs for every layer

    //allocate memory for new weights

    //compute new weights

    //free current weights

    //update MLP with new weights
}

void train(mlp* n, int target, size_t t_len, double* input, size_t i_len)
{
    //exit clauses
    
    if (n->layers[0].w != i_len)
    {
        printf("input length mismatch, input is %zu and network input is %zu\n", i_len, n->layers[0].w);
        return;
    }
    if (n->layers[n->count-1].w != t_len)
    {
        printf("output length mismatch");
        return;
    }

    //get target array
    
    double* target_array = calloc(t_len, sizeof(double));
    get_target_array(target_array, target, t_len);
    
    //apply gradient descent
    
    gradient_descent(n, target_array, input);
    
    //free memory allocations
    
    free(target_array);
}
