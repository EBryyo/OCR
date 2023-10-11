#include "../mlp/mlp.h"
#include "../layer/layer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

double* target_array(int target, size_t len)
{
    //creates target array
    double* res = calloc(len, sizeof(double));
    for (size_t i = 0; i < len; i++)
    {
	res[i] = (i == target) ? 0.97 : 0.03;
    }
    return res;
}

void gradient_descent(double* input, double* target, Mlp* n)
{
    //updates weights of network using gradient descent
}

void train(double* input, int target, Mlp* network, size_t len)
{
    //wrapper of gradient descent
    if (len != network->layers[0].h)
    {
	printf("input size mismatch\n");
	return;
    }

    double* target = target_array(target, network->layers[network->count-1].w);

    gradient_desent(input, target, network);

    free(target);
}
