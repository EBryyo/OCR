#include "../mlp/mlp.h"
#include "../layer/layer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

#define LEARNING_RATE 0.5

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
    return output[i] - target[i];
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

double sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double d_sigmoid(double x)
{
    return sigmoid(x) * (1 - sigmoid(x));
}

void gradient_descent(double* input, double* target, Mlp* n)
{
    //updates weights of network using gradient descent
    size_t i, w, h, ww;
    double sum;
    double** error; 
    double** activation;
    double cost;

    //allocate memory for error
    error = calloc(n->count, sizeof(double*));

    //allocate memory for each layer's error
    for(i = 0; i < n->count; i++)
    {
        error[i] = calloc(n->layers[i].w, sizeof(double));
    }

    //get activation of mlp with given input
    activation = get_activation(input, n);

    //compute gradient
    for(i = n->count - 1; i <= n->count; i--)
    {
        if (i == n->count - 1)
        {
            //compute error for output layer
            for(w = 0; w < n->layers[i].w; w++)
            {
                //get error for w-th output
                cost = get_cost(activation[n->count-1], target, w);
                sum = 0;
                for(ww = 0; ww < n->layers[i].h; ww++)
                {
                    sum += (activation[i-1][ww] * n->layers[i].weights[w][ww]);
                }
                sum += n->layers[i].biases[w];
                error[i][w] = d_sigmoid(sum) * cost;
            }
        }
        else
        {
            //compute error for hidden layer
            for(w = 0; w < n->layers[i].w; w++)
            {
                //get neuron error
                cost = 0;
                sum = 0;
                for(h = 0; h < n->layers[i].h; h++)
                {
                    sum += (i ? activation[i-1][h] : input[h]) * 
                        n->layers[i].weights[w][h];
                }
                for(h = 0; h < n->layers[i+1].w; h++)
                {
                    cost += n->layers[i+1].weights[h][w] * error[i+1][h];
                }
                error[i][w] = d_sigmoid(sum) * cost;
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
                
                 n->layers[i].weights[w][h] -= 
                        LEARNING_RATE * error[i][w] * 
                            ((i) ? activation[i-1][h] : input[h]);
            }
        }
    }

    //apply gradient to biases
    for(i = 0; i < n->count; i++)
    {
        for(w = 0; w < n->layers[i].w; w++)
        {
            n->layers[i].biases[w] -= 
                LEARNING_RATE * error[i][w];
        }
    }

    //free error and activation
    for(i = 0; i < n->count; i++)
    {
        free(error[i]);
        free(activation[i]);
    }
    free(error);
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
