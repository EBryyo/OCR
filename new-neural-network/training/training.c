#include "../mlp/mlp.h"
#include "../layer/layer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

#define LEARNING_RATE 1

double* target_array(int target, size_t len)
{
    //creates target array
    double* res = calloc(len, sizeof(double));
    for (size_t i = 0; i < len; i++)
    {
        res[i] = (i == target) ? 1 : 0;
    }
    return res;
}

double get_cost(double* output, double* target, size_t i)
{
    return LEARNING_RATE * pow((target[i] - output[i]),2);
}

double get_total_cost(double* output, double* target, size_t len)
{
    double res = 0;
    for(size_t i = 0; i < len; i++)
    {
        res += get_cost(output, target, i);
    }
    return res;
}

void gradient_descent(double* input, double* target, Mlp* n)
{
    //updates weights of network using gradient descent
    size_t i, w, h, ww;
    double*** gradient; //weights
    double** gradient_b; //biases
    double** activation;
    double cost;

    //allocate memory for gradient
    gradient = calloc(n->count, sizeof(double**));
    gradient_b = calloc(n->count, sizeof(double*));

    //allocate memory for each layer's gradient
    for(i = 0; i < n->count; i++)
    {
        gradient[i] = calloc(n->layers[i].w, sizeof(double*));
        gradient_b[i] = calloc(n->layers[i].w, sizeof(double));
        //allocate memory for each neuron's weights
        for(w = 0; w < n->layers[i].w; w++)
        {
            gradient[i][w] = calloc(n->layers[i].h, sizeof(double));
        }
    }

    //get activation of mlp with given input
    activation = get_activation(input, n);

    //compute gradient
    for(i = n->count - 1; i <= n->count; i--)
    {
        if (i == n->count - 1)
        {
            //compute gradient for output layer
            for(w = 0; w < n->layers[i].w; w++)
            {
                //get error for wth output
                cost = get_cost(activation[n->count-1], target, w);
                for(h = 0; h < n->layers[i].h; h++)
                {
                    //process weight gradient (gradient[i][w][h])
                }
            }
        }
        else
        {
            //compute gradient for hidden layer
            for(w = 0; w < n->layers[i].w; w++)
            {
                //get neuron gradient
                cost = 0;
                for (ww = 0; ww < n->layers[i+1].w; ww++)
                {
                    cost += gradient[i+1][ww][w];
                }
                for(h = 0; h < n->layers[i].h; h++)
                {
                    //process weight gradient (gradient[i][w][h])
                }
            }
        }
    }



    //apply gradient to weights
    for(i = 0; i < n->count; i++)
    {
        for(w = 0; w < n->layers[i].w; w++)
        {
            for(h = 0; h < n->layers[i].h; h++)
            {
            n->layers[i].weights[w][h] += gradient[i][w][h];
            }
        }
    }

    //apply gradient to biases
    for(i = 0; i < n->count; i++)
    {
        for(w = 0; w < n->layers[i].w; w++)
        {
            n->layers[i].biases[w] += gradient_b[i][w];
        }
    }

    //free gradients and activation
    for(i = 0; i < n->count; i++)
    {
        for(w = 0; w < n->layers[i].w; w++)
        {
            free(gradient[i][w]);
        }
        free(gradient[i]);
        free(gradient_b[i]);
        free(activation[i]);
    }
    free(gradient);
    free(gradient_b);
    free(activation);
}

void train(double* input, int target, Mlp* network, size_t len)
{
    //wrapper of gradient descent
    if (len != network->layers[0].h)
    {
        printf("input size mismatch\n");
        return;
    }

    double* targetarray = target_array(target, network->layers[network->count-1].w);

    gradient_descent(input, targetarray, network);

    free(targetarray);
}
