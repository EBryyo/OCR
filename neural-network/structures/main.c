#include <stdio.h>
#include <stddef.h>
#include "layer.h"
#include "mlp.h"
#include <stdlib.h>

void main(void)
{
    mlp* n;
    n = init(784, 100, 10);
    export_mlp(n, "network");
    free_mlp(n);
    mlp* m = import_mlp("network");
    //export_mlp(m,"network2");
    print_mlp(m);
    /*
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
