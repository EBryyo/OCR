#include "layer.h"
#include "mlp.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

unsigned char maxindex(double* array, size_t len)
{
    unsigned char res = 0;
    for(unsigned char i = 1; i < len; i++)
    {
        if (array[res] < array[i])
            res = i;
    }
    free(array);
    return res;
}

mlp* init(size_t count, size_t* layers)
{
    mlp* n;
    n = calloc(1,sizeof(mlp));
    n->count = count;
    n->layers = calloc(count, sizeof(Layer));
    
    n->layers[0].w = layers[0];
    n->layers[0].h = 1;
    n->layers[0].passive = 1;
    for(size_t i = 1; i < count; i++)
    {
        n->layers[i].passive = 1;
        n->layers[i].w = layers[i];
        n->layers[i].h = n->layers[i-1].w;
        n->layers[i].weights = calloc(layers[i], sizeof(double*));
        n->layers[i].biases = calloc(layers[i], sizeof(double));
        for(size_t j = 0; j < n->layers[i].w; j++)
        {
            n->layers[i].weights[j] = calloc(layers[i-1], sizeof(double));
            for (size_t k = 0; k < n->layers[i].h; k++)
            {
                n->layers[i].weights[j][k] = 1;
            }
        }
    }

    return n;
}

void free_mlp(mlp* network)
{

    //free_layer(network->input_layer);
    //free_layer(network->hidden_layer);
    //free_layer(network->output_layer);
    for(size_t i = 0; i < network->count; i++)
    {
        free_layer(network->layers[i]);
    }
    free(network->layers);
    free(network);
}

double** compute(mlp* network, double* input, size_t len)
{
    double **res;
    double *i, *o;

    res = calloc(network->count - 1, sizeof(double*));

    if (len != network->layers[0].w)
    {
        printf("input size is inappropriate!\n");
        return 0;
    }
    
    i = calloc(len, sizeof(double));
    memcpy(i, input, len * sizeof(double));
    o = calloc(len, sizeof(double));
    for(size_t k = 1; k < network->count; k++)
    {
        compute_output(network->layers[k], i, o);
        free(i);
        res[k-1] = o;
        i = o;
        o = calloc(network->layers[k].w, sizeof(double));
    }

    /*
    unsigned char res = 0;
    for(unsigned char c = 1; c < network->layers[network->count - 1].w; c++)
    {
        if (i[res] > i[c])
            res = c;
    }
    
    return res;

    */
    return res;
}

mlp* import_mlp(char* source)
{
    mlp* n;
    Layer* l;
    size_t i, w, h;
    FILE* file = fopen(source,"rb");
    
    if (file == NULL)
    {
        printf("binary file must exist.");
        return n;
    }

    //allocate memory for n
    n = calloc(1, sizeof(mlp));

    //read layer count from file
    fread(&n->count, sizeof(size_t), 1, file);

    //allocate memory for layer count
    n->layers = calloc(n->count, sizeof(Layer));

    //configure input layer
    fread(&n->layers[0].w, sizeof(size_t), 1, file);
    n->layers[0].h = 1;
    n->layers[0].passive = 1;

    //configure other layers
    for(i = 1; i < n->count; i++)
    {
        l = &n->layers[i];
        fread(&l->w, sizeof(size_t), 1, file);
        l->h = n->layers[i-1].w;
        l->passive = 0;
        l->biases = calloc(l->w, sizeof(double));
        l->weights = calloc(l->w, sizeof(double*));
        fread(l->biases, sizeof(double), l->w, file);
        for(w = 0; w < l->w; w++)
        {
            l->weights[w] = calloc(l->h, sizeof(double));
            fread(l->weights[w], sizeof(double), l->h, file);
        }
    }

    fclose(file);
    return n;
}

void export_mlp(mlp* n, char* destination)
{
    FILE* file;
    file = fopen(destination, "wb");
    size_t i, w, h;

    //write layer count into file
    fwrite(&n->count, sizeof(size_t), 1, file);

    //write input layer neuron count into file
    fwrite(&n->layers[0].w, sizeof(size_t), 1, file);
    

    //for each layer, write count, biases and weights
    //first the neuron count of the layer is written in file
    //then the entire biases array is written in file
    //then the weights matrix is written column by column in file
    for(i = 1; i < n->count; i++)
    {
        fwrite(&n->layers[i].w, sizeof(size_t), 1, file);
        fwrite(n->layers[i].biases, sizeof(double), n->layers[i].w, file);
        h = n->layers[i].h;
        for(w = 0; w < n->layers[i].w; w++)
        {
            fwrite(n->layers[i].weights[w], sizeof(double), h, file);
        }
    }

    fclose(file);
}

void print_mlp(mlp* n)
{
    size_t w,h;

    printf("MULTI-LAYER PERCEPTRON\n");
    printf("\nLAYER 0\n");
    printf("\nCOUNT : %zu\n\n", n->layers[0].w);
    

    for(size_t i = 1; i < n->count; i++)
    {
        printf("LAYER %zu\n\n", i);
        printf("COUNT : %zu\n\n", n->layers[i].w); 
        for(w = 0; w < n->layers[i].w; w++)
        {
            printf("sigmoid %zu :\n", w);
            printf("\tbias : %2g\n", n->layers[i].biases[w]);
            printf("\tweights : ");
            for(h = 0; h < n->layers[i].h; h++)
            {
                printf("%2g ", n->layers[i].weights[w][h]);
            }
            printf("\n");
        }
        printf("\n");
    }
}
