#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "../mlp/mlp.h"
#include "../layer/layer.h"
#include "../training/mnist.h"
#include "../training/training.h"

double randfrom(double min, double max)
{
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

void trainXOR(void)
{
    Mlp* n = import_network("networks/XOR");
    srand(time(NULL));
    size_t p = 0;
    int o;
    int i, j;
    Mlp* n = import_mlp("networks/XOR");
    double* x = calloc(2, sizeof(double));
    for(size_t k = 0; k < 1000; k++)
    {
	i = (rand() & 1);
	j = (rand() & 1);
	x[0] = (double) i;
	x[1] = (double) j;
	train(x, i ^ j, n, 2);
    }
    free(x);
    export_mlp("networks/XOR",n);
}

void trainOCR(void)
{
    Mlp* n = import_network("networks/OCR");
    size_t i, count;
    count = 60000
    load_mnist();
    srand(time(NULL));
    for(size_t k = 0; k < count; k++)
    {
	i = randfrom(0, 60000);
	train(train_images[i], train_labels[i], n, 28*28);
    }
    export_mlp("networks/OCR", n);
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("invalid argument count\n");
        return 1;
    }
    if (!strcmp(argv[1], "XOR"))
    {
        trainXOR();
    }
    else 
    {
        if (!strcmp(argv[1], "OCR"))
            trainOCR();
        else
        {
            printf("invalid routine\n");
            return 1;
        }
    }
    return 0;
}
