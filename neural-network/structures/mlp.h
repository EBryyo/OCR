#include <stddef.h>
#include "layer.h"

#ifndef MLP_H
#define MLP_H

typedef struct
{
    Layer* layers; //array of layers, including input and output layers
    size_t count; //number of layers, including input and output layers
} mlp;


mlp* init(size_t count, size_t* layers);
//initializes a network with appropriate sigmoid counts on each layer

void free_mlp(mlp* network);
//frees memory allocated to network and its fields

double** compute(mlp* network, double* input);
//computes input array through the MLP and returns the output array

mlp* import_mlp( char* source);
//returns mlp encoded at source

void export_mlp(mlp* network, char* destination);
//exports sigmoid weights and biases into binary file at destination

void print_mlp(mlp* n);
//prints lengths of all layers
#endif
