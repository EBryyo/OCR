#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "mlp/mlp.h"
#include "layer/layer.h"

int main(int argc, char** argv)
{
    Mlp* n;
    if (argc < 4)
    {
        printf("invalid argument count\n");
        return 1;
    }

    char* name = argv[1];
    size_t* counts = calloc(argc-2, sizeof(size_t));
    for(size_t i = 0; i < argc - 2; i++)
    {
        sscanf(argv[i+2],"%zu", &counts[i]);
    }
    n = init(argc-2, counts);
    print_mlp(n);
    export_mlp(name, n);
    free(counts);
    //n = import_mlp(name);
    //print_mlp(n);
    //export_mlp(name, n);
    return 0;
}
