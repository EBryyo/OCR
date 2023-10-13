#include "layer.h"
#include <stdlib.h>
#include <math.h>
#include <stddef.h>

double* activation(Layer layer, double* input)
{
    size_t w, h;

    double* res = calloc(layer.w, sizeof(double));
    
    for(w = 0; w < layer.w; w++)
    {
        res[w] = 0;
        for(h = 0; h < layer.h; h++)
        {
            res[w] += (input[h] * layer.weights[w][h]);
        }
        res[w] = 1.f / (1.f + exp(-res[w]));
    }

    return res;
}
