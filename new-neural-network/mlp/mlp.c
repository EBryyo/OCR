#include "../layer/layer.h"
#include "mlp.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

double randfrom(double min, double max)
{
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

Mlp* init(size_t count, size_t* layers)
{
    //initializes MLP with count-1 layers 
    size_t i, w, h;
    Mlp* n = calloc(1, sizeof(Mlp));

    //set layer count
    n->count = count-1;

    //allocate memory for layers;
    n->layers = calloc(count-1, sizeof(Layer));

    //set input count
    n->layers[0].h = layers[0];

    //for each layer
    for(i = 0; i < n->count; i++)
    {
        //parameter matrix dimensions
        if (i)
            n->layers[i].h = n->layers[i-1].w;
        n->layers[i].w = layers[i+1];

        //initialize weights and biases
        n->layers[i].biases = calloc(n->layers[i].w, sizeof(double));
        n->layers[i].weights = calloc(n->layers[i].w, sizeof(double*));

        //initialize each bias
        for(w = 0; w < n->layers[i].w; w++)
        {
            n->layers[i].biases[w] = 0;
        }

        //for each neuron
        for(w = 0; w < n->layers[i].w; w++)
        {
            //allocate memory for weights
            n->layers[i].weights[w] = calloc(n->layers[i].h, sizeof(double));

            //intialize each weight
            for(h = 0; h < n->layers[i].h; h++)
            {
                n->layers[i].weights[w][h] = randfrom(-1,1);
            }
        }
    }

    return n;
}

Mlp* import_mlp(char* source)
{
    Mlp* n;
    size_t i, w;
    //returns the mlp with parameters encoded in file
    FILE* file = fopen(source, "rb");
    n = calloc(1, sizeof(Mlp));

    //read layer count
    fread(&n->count, sizeof(size_t), 1, file);
    
    //allocate memory for layers
    n->layers = calloc(n->count, sizeof(Layer));
    
    //set neuron counts for each layer
    fread(&n->layers[0].h, sizeof(size_t), 1, file);
    for(i = 0; i < n->count; i++)
    {
        if (i != 0)
            n->layers[i].h = n->layers[i-1].w;
        fread(&n->layers[i].w, sizeof(size_t), 1, file);
    }

    //for each layer
    for(i = 0; i < n->count; i++)
    {
        //allocate memory for weights and biases
        n->layers[i].biases = calloc(n->layers[i].w, sizeof(double));
        n->layers[i].weights = calloc(n->layers[i].w, sizeof(double*));

        //read biases from file
        fread(n->layers[i].biases, sizeof(double), n->layers[i].w, file);

        //for each neuron
        for(w = 0; w < n->layers[i].w; w++)
        {
            //allocate memory for weights
            n->layers[i].weights[w] = calloc(n->layers[i].h, sizeof(double));

            //read weights from file
            fread(n->layers[i].weights[w], sizeof(double), 
                    n->layers[i].h, file);
        }
    }

    return n;
    fclose(file);
}

void export_mlp(char* target, Mlp* n)
{
    //encodes parameters of network in file
    FILE* file = fopen(target, "wb");
    size_t i, j, w, h;

    //write layer count in file
    fwrite(&n->count, sizeof(size_t), 1, file);

    //write each layer's neuron count in file
    fwrite(&n->layers[0].h, sizeof(size_t), 1, file);
    for(i = 0; i < n->count; i++)
    {
        fwrite(&n->layers[i].w, sizeof(size_t), 1, file);
    }

    //for each layer
    for(i = 0; i < n->count; i++)
    {
        //write all biases in file
        fwrite(n->layers[i].biases, sizeof(double), n->layers[i].w, file);
        //for each neuron
        for(w = 0; w < n->layers[i].w; w++)
        {
            //write all weights in file
            fwrite(n->layers[i].weights[w], 
                    sizeof(double), n->layers[i].h, file);
            free(n->layers[i].weights[w]);
        }
        free(n->layers[i].biases);
        free(n->layers[i].weights);
    }

    fclose(file);
    free(n->layers);
    free(n);

}

double** get_activation(double* input, Mlp* n)
{
    //returns the activations of each layer with a given input
    double** act;

    act = calloc(n->count, sizeof(double*));
    
    act[0] = activation(n->layers[0], input);
    /*
    for(size_t j = 0; j < n->layers[0].w; j++)
    {
        printf("%g ", act[0][j]);
    }
    printf("\n");
    */

    for (size_t i = 1; i < n->count; i++)
    {
        act[i] = activation(n->layers[i], act[i-1]);
        /*
        for(size_t j = 0; j < n->layers[i].w; j++)
        {
            printf("%g ", act[i][j]);
        }
        printf("\n");
        */
    }

    return act;
}

int compute_output(double* input, Mlp* n)
{
    //returns the final output of the MLP with a given input
    size_t i, r;
    double cur;

    double** activation = get_activation(input, n);
    double* output = activation[n->count - 1];
     
    cur = output[0];
    r = 0;
    for(i = 1; i < n->layers[n->count-1].w; i++)
    {
        if (output[i] > cur)
        {
            r = i;
            cur = output[i];
        }
    }

    //free the activation matrix from heap
    for(i = 0; i < n->count; i++)
    {
        free(activation[i]);
    }
    free(activation);
    return (int)r;
}

void print_mlp(Mlp* n)
{
    size_t i, w, h;
    printf("MULTI LAYER PERCEPTRON\n\n");
    printf("Layer 0:\n\n\tCount: %zu\n\n", n->layers[0].h);
    for(i = 0; i < n->count; i++)
    {
        printf("Layer %zu:\n\n\tCount: %zu\n\n", i+1, n->layers[i].w);
        printf("\tbiases:  ");
        for(w = 0; w < n->layers[i].w; w++)
        {
            printf(" %3g", n->layers[i].biases[w]);
        }
        printf("\n\n");
        for(w = 0; w < n->layers[i].w; w++)
        {
            printf("\tneuron %zu:", w);
            for(h = 0; h < n->layers[i].h; h++)
            {
                printf(" %3g", n->layers[i].weights[w][h]);
            }
            printf("\n");
        }
        printf("\n");
    }
}
