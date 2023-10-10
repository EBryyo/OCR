#include <stdio.h>
#include "training/mnist.h"
#include <stddef.h>
#include <stdlib.h>
#include "mlp/mlp.c"
#include "layer/layer.c"

void testXOR()
{
    Mlp* n = import_mlp("networks/XOR");
    double* x = calloc(2, sizeof(double));

    for(size_t i = 0; i < 100; i++)
    {
        x[0] = rand() % 2;
        x[1] = rand() % 2;

        printf("test %i: | %i | %i | => %i\n",
                i, x[0], x[1], compute_output(x, n));
    }
}

void testOCR()
{
    Mlp* n = import_mlp("networks/OCR");
    load_mnist();
    for(size_t i = 0; i < 10000; i++)
    {
        printf("test %i:\n\texpected: %i\tactual: %i\n",
                i, train_label[i], compute_output(train_image[i], n));
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2)
        printf("invalid argument count\n");
        return 1;
    if (argv[1] == "XOR")
        testXOR();
    else if (argv[1] == "OCR")
        testOCR();
    else
    {
        printf("invalid test\n");
        return 1;
    }

    return 0;
}
