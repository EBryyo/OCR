#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "../mlp/mlp.h"
#include "../layer/layer.h"
#include "../training/mnist.h"
#include "../training/training.h"
#include <time.h>


double testOCR(Mlp* n)
{
    double res;
    size_t p = 0;
    int o;
    size_t sample = 10000;
    load_mnist();
    for(size_t i = 0; i < sample; i++)
    {
        o = compute_output(train_image[i],n);
        if (o == train_label[i]) 
            p++;
    }
    res = (double) p  * 100/ (double) sample;
    printf("\nAccuracy : %g percent\n", res);
    return (res);
}

void trainXOR(void)
{
    Mlp* n = import_mlp("networks/XOR");
    srand(time(NULL));
    size_t p = 0;
    int o;
    int i, j;
    double* x = calloc(2, sizeof(double));
    for(size_t k = 0; k < 10000; k++)
    {
        i = (rand() & 1);
        j = (rand() & 1);
        x[0] = (double) i;
        x[1] = (double) j;
        train(x, i != j, n, 2);
    }
    free(x);
    export_mlp("networks/XOR",n);
}

void trainOCR(void)
{
    Mlp* n;
    n = import_mlp("networks/OCR");
    size_t i, count;
    count = 60000;
    load_mnist();
    srand(time(NULL));
    do {
        export_mlp("networks/OCR", n);
        n = import_mlp("networks/OCR");
        for(size_t k = 0; k < count; k++)
        {
            i = randfrom(0, 60000);
            train(train_image[i], train_label[i], n, 28*28);
        }
    } while (testOCR(n) < 99);
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
