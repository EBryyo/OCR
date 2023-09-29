#include <stdio.h>
#include <math.h>
#include <stddef.h>
#include "mnist.h"
#include "../structures/mlp.h"
#include "../structures/layer.h"


double* get_target_array(int i, size_t len)
{ //returns the desired output array for a given digit
    double* res = calloc(len, sizeof(int));
    res[i] = 0.99;
    for(size_t n = 0; n < len; n++)
    {
        if (n != i)
        {
            res[n] = 0.01;
        }
    }
    return res;
}


void main(void)
{
    load_mnist();
    mlp* n = import_mlp("network");
    //train image :
    //  train_image[60000][784] (type: double, normalized, flattened)
    //train label :
    //  train_label[60000] (type: int)
    //test image : 
    //  test_image[10000][784] (type: double, normalized, flattened)
    //test label : 
    //test_label[10000] (type: int)
    print_mlp(n);

    export_mlp(n, "network");
}
