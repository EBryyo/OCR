#include "../layer/layer.h"
#include "mlp.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void free_mlp(Mlp* n)
{
    //frees MLP from heap memory
    
}

Mlp* init(size_t count, size_t* layers)
{
    //initializes MLP with count-1 layers 
        
}

Mlp* import_mlp(char* source)
{
    Mlp* n;
    //returns the mlp with parameters encoded in file
    FILE* file = fopen(source, "rb");
    n = calloc(1, sizeof(Mlp));

    //read layer count
    fread(&n->count, sizeof(size_t), 1, file);
    
    fclose(file);
}

void export_mlp(char* file, Mlp* n)
{
    //encodes parameters of network in file
    FILE* file = fopen(source, "wb");
    size_t i, j, w, h;

    //write layer count in file
    fwrite(&n->count, sizeof(size_t), 1, file);

    //write each layer's neuron coutn in file
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
        }
    }

    fclose(file);
    free_mlp(n);

}

double** get_activation(double* input, Mlp* n)
{
    //returns the activations of each layer with a given input

}

int compute_output(double* input, Mlp* n)
{
    //returns the final output of the MLP with a given input

}

void print_mlp(Mlp* n)
{
    
}
