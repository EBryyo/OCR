#include "../mlp/mlp.h"
#include "../layer/layer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

#define LEARNING_RATE 0.1

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

double** gradient_descent(double* input, double* target, Mlp* n, double*** a)
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
    *a = activation;

    //compute error
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
    /*
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
    */

    //apply gradient to biases
    /*
    for(i = 0; i < n->count; i++)
    {
        for(w = 0; w < n->layers[i].w; w++)
        {
            n->layers[i].biases[w] -= 
                LEARNING_RATE * error[i][w];
        }
    }
    */

    //free error and activation
    for(i = 0; i < n->count; i++)
    {
        //free(error[i]);
        //free(activation[i]);
    }
    //free(error);
    //free(activation);
    
    return error;
}

double** average_error(Mlp* n, double*** errors, size_t batch_size)
{
    size_t i, w, k;
    double** err = calloc(n->count, sizeof(double*));
     
    for(i = 0; i < n->count; i++)
    {
        err[i] = calloc(n->layers[i].w, sizeof(double));
        for(w = 0; w < n->layers[i].w; w++)
        {
            err[i][w] = 0;
            for (k = 0; k < batch_size; k++)
            {
                err[i][w] += errors[k][i][w];
            }
            err[i][w] /= batch_size;
        }
    }

    return err;
}

void train(double** input, int* target, Mlp* network, size_t len, 
        size_t batch_size)
{
    size_t i, j, w, h;
    double** activation;
    double** error; //average error
    double*** errors; //errors for each batch member
    double*** activations;
    //wrapper of gradient descent
    if (len != network->layers[0].h)
    {
        printf("input size mismatch\n");
        return;
    }
    
    activations = calloc(batch_size, sizeof(double**));
    errors = calloc(batch_size, sizeof(double**));

    for(i = 0; i < batch_size; i++)
    {
        double* targetarray = target_array(target[i], 
                network->layers[network->count-1].w);
        errors[i] = gradient_descent(input[i], targetarray, network, 
                &activations[i]);
        free(targetarray);
    }

    //compute average error
    error = average_error(network, errors, batch_size);
    activation = average_error(network, activations, batch_size);

    //compute input average
    double* input_avg = calloc(network->layers[0].h, sizeof(double));
    for(i = 0; i < network->layers[0].h; i++)
    {
        input_avg[i] = 0;
        for(j = 0; j < batch_size; j++)
        {
            input_avg[i] += input[j][i];
        }
        input_avg[i] /= batch_size;

    }

    //apply gradients to network
    
    //apply gradient to weights
    
    for(i = 0; i < network->count; i++)
    {
        for(w = 0; w < network->layers[i].w; w++)
        {
            for(h = 0; h < network->layers[i].h; h++)
            {    
                 network->layers[i].weights[w][h] -= 
                        LEARNING_RATE * error[i][w] * 
                            ((i) ? activation[i-1][h] : input_avg[h]);
            }
        }
    }
    

    //apply gradient to biases
    
    for(i = 0; i < network->count; i++)
    {
        for(w = 0; w < network->layers[i].w; w++)
        {
            network->layers[i].biases[w] -= 
                LEARNING_RATE * error[i][w];
        }
    }

    //free errors
    for(j = 0; j < batch_size; j++)
    {
        for(i = 0; i < network->count; i++)
        {
            free(activations[j][i]);
            free(errors[j][i]);
        }
        free(activations[j]);
        free(errors[j]);
    }
    free(activations);
    free(errors);

    for(i = 0; i < network->count; i++)
    {
        free(activation[i]);
        free(error[i]);
    }
    free(activation);
    free(error);
}
