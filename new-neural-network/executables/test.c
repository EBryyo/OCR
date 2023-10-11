#include <stdio.h>
#include "../training/mnist.h"
#include <stddef.h>
#include <stdlib.h>
#include "../layer/layer.h"
#include "../mlp/mlp.h"
#include <string.h>
#include <time.h>


void testXOR(void)
{
    srand(time(NULL));
    size_t p = 0;
    int o;
    int i, j;
    Mlp* n = import_mlp("networks/XOR");
    double* x = calloc(2, sizeof(double));
    for(size_t k = 0; k < 100; k++)
    {
        i = (rand() & 1);
        j = (rand() & 1);
        x[0] = (double) i;
        x[1] = (double) j;
        o = compute_output(x, n);
        if (o == (i ^ j))
            p++;
        printf("test %i: | %g | %g | => %i, should be %i\n",
                k, x[0], x[1], o, i ^ j);
    }
    printf("\nAccuracy : %i percent\n", p);
    free(x);
    export_mlp("networks/XOR",n);
}

void testOCR(void)
{
    size_t p = 0;
    int o;
    Mlp* n = import_mlp("networks/OCR");
    load_mnist();
    for(size_t i = 0; i < 10000; i++)
    {
        o = compute_output(train_image[i],n);
        if (o == train_label[i]) 
            p++;
        printf("test %i:\n\texpected: %i\tactual: %i\n",
                i, train_label[i], o);
    }
    printf("\nAccuracy : %g percent\n", (double)10000 / (double)p);
    export_mlp("networks/OCR", n);
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("invalid argument count\n");
        return 1;
    }
    if (!strcmp(argv[1], "XOR"))
    {
        testXOR();
    }
    else 
    {
        if (!strcmp(argv[1], "OCR"))
            testOCR();
        else
        {
            printf("invalid test\n");
            return 1;
        }
    }
    return 0;
}
