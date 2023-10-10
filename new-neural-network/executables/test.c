#include <stdio.h>
#include "../training/mnist.h"
#include <stddef.h>
#include <stdlib.h>
#include "../layer/layer.h"
#include "../mlp/mlp.h"
#include <string.h>

void testXOR(void)
{
    printf("coucou\n");
    Mlp* n = import_mlp("networks/XOR");
    double* x = calloc(2, sizeof(double));
    print_mlp(n);
    for(size_t i = 0; i < 100; i++)
    {
        x[0] = (double) (rand() & 1);
        x[1] = (double) (rand() & 1);

        printf("test %i: | %g | %g | => %i\n",
                i, x[0], x[1], compute_output(x, n));
    }
}

void testOCR(void)
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
