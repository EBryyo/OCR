#ifndef MLP_H
#define MLP_H

typedef struct {
    size_t count; //number of layers (excluding input layer)
    Layer *layers; //layers
} Mlp;

Mlp* init(size_t count, size_t* layers);
//initializes MLP with count-1 layers 

Mlp* import_mlp(char* source);
//returns the mlp with parameters encoded in file

void export_mlp(char* file, Mlp* n);
//encodes parameters of network in file

double** get_activation(double* input, Mlp* n);
//returns the activations of each layer with a given input

int compute_output(double* input, Mlp* n);
//returns the final output of the MLP with a given input

#endif
