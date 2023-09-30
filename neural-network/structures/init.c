#include <stdio.h>
#include <stddef.h>
#include "layer.h"
#include "mlp.h"
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[])
{
    mlp *network;

    if (argc < 3)
    {
        printf("incorrect argument count\n");
        return 1;
    }

    size_t* layers = calloc(argc-2, sizeof(size_t));
    for(size_t i = 2; i < argc; i++)
    {
        sscanf(argv[i],"%zu", &layers[i-2]);
    }
    network = init(argc-2, layers);
    export_mlp(network, argv[1]);
    print_mlp(network);
    free_mlp(network);
    free(layers);
    /*
    size_t layers[3] = {28*28, 100, 10};
    n = init(3, layers);
    export_mlp(n, "network");
    printf("1\n");
    free_mlp(n);
    printf("1\n");
    m = import_mlp("network");
    print_mlp(m);
    free_mlp(m);
    
    size_t i;
    mlp* neural_net = calloc(1, sizeof(mlp));
    //malloc for input layer
    neural_net->input_layer.w = 3;
    neural_net->input_layer.h = 1;
    neural_net->input_layer.weights = calloc(3,sizeof(double*));
    for(i = 0; i < neural_net->input_layer.w; i++)
    {
        neural_net->input_layer.weights[i] = calloc(1,sizeof(double));
    }
    //malloc for hidden layer
    neural_net->hidden_layer.w = 2;
    neural_net->hidden_layer.h = 3;
    neural_net->hidden_layer.weights = calloc(2, sizeof(double*));
    for(i = 0; i < neural_net->hidden_layer.w; i++)
    {
        neural_net->hidden_layer.weights[i] = calloc(3,sizeof(double));
    }
    //malloc for output layer
    neural_net->output_layer.w = 1;
    neural_net->output_layer.h = 2;
    neural_net->output_layer.weights = calloc(1, sizeof(double*));
    for(i = 0; i < neural_net->output_layer.w; i++)
    {
        neural_net->output_layer.weights[i] = calloc(2,sizeof(double));
    }


    neural_net->output_layer.weights = calloc(1, sizeof(double*));
    neural_net->output_layer.weights[0] = calloc(2, sizeof(double));
    neural_net->input_layer.weights[0][0] = 1;
    neural_net->input_layer.weights[1][0] = 2;
    neural_net->input_layer.weights[2][0] = 3;
    neural_net->hidden_layer.weights[0][0] = -1;
    neural_net->hidden_layer.weights[0][1] = -2;
    neural_net->hidden_layer.weights[1][2] = 3;
    neural_net->hidden_layer.weights[1][0] = -2;
    neural_net->output_layer.weights[0][1] = -2;
    neural_net->output_layer.weights[0][0] = 4;



    export_mlp(neural_net, "network");
    */
    //n = import_mlp("network");
    //print_mlp(n);
    //printf("\n");
    //export_mlp(n, "network2");
 }
