#include <stdio.h>
#include <stddef.h>
#include "layer.h"
#include "mlp.h"
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[])
{
    mlp *network;

    if (argc < 3)
    {
        printf("incorrect argument count\n");
        return 1;
    }

    size_t* layers = calloc(argc-2, sizeof(size_t));
    for(size_t i = 2; i < argc; i++)
    {
        sscanf(argv[i],"%zu", &layers[i-2]);
    }
    network = init(argc-2, layers);
    export_mlp(network, argv[1]);
    print_mlp(network);
    free_mlp(network);
    free(layers);
    return 0;
}
