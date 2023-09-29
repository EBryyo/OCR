#include <stdio.h>
#include <stddef.h>
#include "mnist.h"
#include "../structures/mlp.h"
#include "../structures/layer.h"

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
    size_t count = 0;
    double ratio;
    for(size_t i = 0; i < 10000; i++)
    {
        int truc = compute(n, test_image[i], 784);
        printf("Expected : %i    Actual : %i\n", test_label[i],truc);
        if (test_label[i] == truc)
        {
            count++;
        }
    }
    printf("Accuracy = %2g%\n", (double)10000/count);
}
