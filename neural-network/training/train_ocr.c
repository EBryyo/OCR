#include <stdio.h>
#include <stddef.h>
#include "../structures/mlp.h"
#include "../structures/layer.h"
#include "training.h"
#include "mnist.h"
#include <stdlib.h>


int main(int argc, char** argv)
{

    mlp* n = import_mlp("../networks/OCR");
    
    load_mnist();
    //train image :
    //  train_image[60000][784] (type: double, normalized, flattened)
    //train label :
    //  train_label[60000] (type: int)
    //test image : 
    //  test_image[10000][784] (type: double, normalized, flattened)
    //test label : 
    //test_label[10000] (type: int)
    
    for(size_t i = 0; i < 1000; i++)
    {
        train(n, train_label[i], 10, train_image[i], 28 * 28);
    }

    //print_mlp(n);
    export_mlp(n, "../networks/OCR");
    free_mlp(n);
}
