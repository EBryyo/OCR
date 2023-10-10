#include <stdio.h>
#include "training/mnist.h"
#include <stddef.h>
#include <stdlib.h>

void testXOR()
{
    Mlp* n = import_mlp("networks/XOR");
    int* x = calloc(2, sizeof(int));

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

int main(int argc, char* argc[])
{
    if (argc != 2)
        printf("invalid argument count\n");
        return 1;
    switch(argc[1])
    {
        case "XOR":
            testXOR();
            break;
        case "OCR":
            testOCR();
            break;
        default:
            printf("invalid test\n");
            return 1;
    }

    return 0;
}
