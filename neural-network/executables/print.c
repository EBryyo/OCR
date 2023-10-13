#include "../mlp/mlp.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("invalid argument count\n");
        return 1;
    }
    if (!strcmp(argv[1], "XOR"))
    {
        Mlp* n = import_mlp("networks/XOR");
        print_mlp(n);
        export_mlp("networks/XOR", n);
    }
    else 
    {
        if (!strcmp(argv[1], "OCR"))
        {
            Mlp* n = import_mlp("networks/OCR");
            print_mlp(n);
            export_mlp("networks/OCR", n);
        }
        else
        {
            printf("invalid test\n");
            return 1;
        }
    }
    return 0;
}
