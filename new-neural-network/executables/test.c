#include <stdio.h>
#include "../training/mnist.h"
#include <stddef.h>
#include <stdlib.h>
#include "../layer/layer.h"
#include "../mlp/mlp.h"
#include <string.h>
#include <time.h>

void print_result(int x)
{
    if (x)
        printf("\033[1;32mCORRECT\033[0m\n");
    else
        printf("\033[1;31mINCORRECT\033[0m\n");
}

void testXOR(void)
{
    srand(time(NULL));
    size_t p = 0;
    int o;
    int i, j;
    Mlp* n = import_mlp("networks/XOR");

    double input[2] = {0,0};
    o = compute_output(input, n);
    printf("\n\t0 ^ 0 -> %i\t", o);
    print_result(o == 0);
    input[0] = 1;
    o = compute_output(input, n);
    printf("\t1 ^ 0 -> %i\t", o);
    print_result(o == 1);
    input[0] = 0;
    input[1] = 1;
    o = compute_output(input, n);
    printf("\t0 ^ 1 -> %i\t", o);
    print_result(o == 1);
    input[0] = 1;
    o = compute_output(input, n);
    printf("\t1 ^ 1 -> %i\t", o);
    print_result(o == 0);
    printf("\n");


    export_mlp("networks/XOR",n);
}

void testOCR(void)
{
    size_t p = 0;
    int o;
    size_t sample = 10000;
    Mlp* n = import_mlp("networks/OCR");
    load_mnist();
    for(size_t i = 0; i < sample; i++)
    {
        o = compute_output(train_image[i],n);
        printf("test %i:%s %i -> %i\t\t",
                i, i < 10 ? "\t\t" : "\t", train_label[i], o);
        if (o == train_label[i])
        {
            p++;
            printf("\033[1;32m");
            printf("CORRECT\n");
        }
        else
        {
            printf("\033[1;31m");
            printf("INCORRECT\n");
        }
        printf("\033[0m");
    }
    printf("\nAccuracy : %g percent\n", (double) p * 100 / (double) sample);
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
