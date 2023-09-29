#include <stddef.h>
#include "layer.h"

#ifndef MLP_H
#define MLP_H

typedef struct
{
    Layer input_layer;

    Layer hidden_layer;

    Layer output_layer;
} mlp;
mlp* init(size_t inputlen, size_t hiddenlen, size_t outputlen);
//initializes a network with appropriate sigmoid counts each layer

void free_mlp(mlp* network);
//frees memory allocated to network and its fields

unsigned char compute(mlp* network, double* input, size_t len);
//computes input array through the MLP and returns the predicted number

mlp* import_mlp( char* source);
//returns mlp encoded at source

void export_mlp(mlp* network, char* destination);
//exports sigmoid weights and biases into binary file at destination

void print_mlp(mlp* n);
//prints lengths of all layers
#endif
