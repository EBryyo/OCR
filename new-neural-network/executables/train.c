#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "../mlp/mlp.h"
#include "../layer/layer.h"
#include "../training/mnist.h"
#include "../training/training.h"
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <err.h>

void swap(size_t x, size_t y, size_t* indexes)
{
    size_t buffer = indexes[x];
    indexes[x] = indexes[y];
    indexes[y] = buffer;
}

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
    printf("Accuracy : %g percent\n", res);
    return (res);
}

void trainXOR(void)
{
    Mlp* n = import_mlp("networks/XOR");
    srand(time(NULL));
    size_t i, w;
    //inertia is an array that stores the previous changes made to each weight
    //it is used to add inertia to the gradient descent algorithm
    double*** inertia = calloc(n->count, sizeof(double**));
    for(i = 0; i < n->count; i++)
    {
	    inertia[i] = calloc(n->layers[i].w, sizeof(double*));
	    for(w = 0; w < n->layers[i].w; w++)
	    {
	        inertia[i][w] = calloc(n->layers[i].h, sizeof(double));
	    }
    }

    size_t p = 0;
    int o;
    int l, j;
    double* x = calloc(2, sizeof(double));
    for(size_t k = 0; k < 10000; k++)
    {
        l = (rand() & 1);
        j = (rand() & 1);
        x[0] = (double) l;
        x[1] = (double) j;
        train(x, l != j, n, 2, inertia);
    }

    //free intertia
    for(i = 0; i < n->count; i++)
    {
        for(size_t w = 0; w < n->layers[i].w; w++)
        {
            free(inertia[i][w]);
        }
        free(inertia[i]);
    }
    free(inertia);
    free(x);
    export_mlp("networks/XOR",n);
}

void trainOCR(void)
{
    Mlp* n;
    n = import_mlp("networks/OCR");
    size_t i, count;
    //inertia is an array that stores the previous changes made to each weight
    //it is used to add inertia to the gradient descent algorithm
    double*** inertia = calloc(n->count, sizeof(double**));
    for(i = 0; i < n->count; i++)
    {
        inertia[i] = calloc(n->layers[i].w, sizeof(double*));
        for(size_t w = 0; w < n->layers[i].w; w++)
        {
            inertia[i][w] = calloc(n->layers[i].h, sizeof(double));
        }
    }
    count = 60000;
    load_mnist();
    srand(time(NULL));
    do {
        export_mlp("networks/OCR", n);
        pid_t id = fork();
        if (id == -1)
        {
            err(1,"fork()");
        }
        if (id)
        {
            size_t* indexes = calloc(count, sizeof(size_t));
            for(i = 0; i < count; i++)
            {
                indexes[i] = i;
            }
            for(i = 0; i < count; i++)
            {
                size_t m = randfrom(0,count);
                swap(i,m,indexes);
            }

            n = import_mlp("networks/OCR");
            for(size_t i = 0; i < count; i++)
            {
                train(train_image[indexes[i]], train_label[indexes[i]], n, 28*28, inertia);
            }
            free(indexes);
            kill(id, 1);
            printf("\033[1A");
        }
        else
        {
            for(i = 0; 1; i = (i + 1) % 4)
            {
                char c;
                switch(i)
                {
                    case 0:
                        c = '/';
                        break;
                    case 1:
                        c = '-';
                        break;
                    case 2:
                        c = '\\';
                        break;
                    default:
                        c = '|';
                }
                printf("\033[1;33m:) I'm learning! %c\033[m\n",c);
                printf("\033[1A");
                printf("\033[20D");
                for(size_t m = 0; m < 500000000; m++)
                {}
            }
        }
    } while (testOCR(n) < 99.5);

    
    for(i = 0; i < n->count; i++)
    {
        for(size_t w = 0; w < n->layers[i].w; w++)
        {
            free(inertia[i][w]);
        }
        free(inertia[i]);
    }
    free(inertia);
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
