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
    //printf("target array obtained.\n");
}

double error(double target, double output)
{
    //computes the error of an output neuron

    return 0.5 * pow((output - target), 2);
}


void gradient_descent(mlp* n, double* target, double* input)
{
    //applies the gradient descent algorithm on MLP n

    double** outputs;
    size_t i, j, k, w, h;
    double err;
    double*** new_weights;

    //compute outputs for every layer
    outputs = compute(n, input);

    //allocate memory for new weights
    new_weights = calloc(n->count - 1, sizeof(double**));
    for(i = 0; i < n->count - 1; i++)
    {
        new_weights[i] = calloc(n->layers[i + 1].w, sizeof(double*));
        for(w = 0; w < n->layers[i + 1].w; w++)
        {
            new_weights[i][w] = calloc(n->layers[i+1].h, sizeof(double));
        }
    }

    //compute new weights
    
    //iterate on each layer
    for(i = 0; i < n->count - 1; i++)
    {
        //iterate on each neuron
        for(w = 0; w < n->layers[i+1].w; w++)
        {
            //iterate on each weight
            for(h = 0; h < n->layers[i+1].h; h++)
            {
                if (i == n->count - 2)
                {
                    //calculation for output layer

                }
                else
                {
                    //calculation for hidden layer
                    
                }
            }
        }
    }
    

    //free current weights
    for(i = 1; i < n->count; i++)
    {
        for(w = 0; w < n->layers[i].w; w++)
        {
            free(n->layers[i].weights[w]);
        }
        free(n->layers[i].weights);
    }
    //update MLP with new weights
    for(i = 1; i < n->count; i++)
    {
        n->layers[i].weights = new_weights[i-1];
    }
    free(new_weights);

    //free outputs array
    for(i = 0; i < n->count - 1; i++)
    {
        free(outputs[i]);
    }
    free(outputs);
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
