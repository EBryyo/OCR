#ifndef MLP_H
#define MLP_H

typedef struct {
    size_t count; //number of layers (excluding input layer)
    Layer *layers; //layers
} Mlp;

Mlp* import_mlp(char* file);
//returns the mlp with parameters encoded in file

void export_mlp(char* file, Mlp* network);
//encodes parameters of network in file

double** get_activation(double* input, Mlp* network);
//returns the activations of each layer with a given input

int compute_output(double* input, Mlp* network);
//returns the final output of the MLP with a given input

#endif
