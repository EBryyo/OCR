#include "layer.h"
#include "mlp.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


unsigned char maxindex(double* array, size_t len)
{
    unsigned char res = 0;
    for(unsigned char i = 1; i < len; i++)
    {
        if (array[res] < array[i])
            res = i;
    }
    free(array);
    return res;
}

mlp* init(size_t inputlen, size_t hiddenlen, size_t outputlen)
{
    mlp* n;
    n = calloc(1,sizeof(mlp));
    n->input_layer.w = inputlen;
    n->input_layer.h = 1;
    n->hidden_layer.w = hiddenlen;
    n->hidden_layer.h = inputlen;
    n->output_layer.w = outputlen;
    n->output_layer.h = hiddenlen;

    size_t i;

    n->input_layer.weights = calloc(inputlen,sizeof(double*));
    n->input_layer.biases = calloc(inputlen,sizeof(double));
    for(i = 0; i < inputlen; i++)
    {
        n->input_layer.biases[i] = 0;
        n->input_layer.weights[i] = calloc(1,sizeof(double));
        n->input_layer.weights[i][0] = 1;
    }

    n->hidden_layer.weights = calloc(hiddenlen,sizeof(double*));
    n->hidden_layer.biases = calloc(hiddenlen,sizeof(double));
    for(i = 0; i < hiddenlen; i++)
    {
        n->hidden_layer.biases[i] = 0;
        n->hidden_layer.weights[i] = calloc(inputlen,sizeof(double));
        for(size_t j = 0; j < inputlen; j++)
        {
            n->hidden_layer.weights[i][j] = 1;
        }
    }

    n->output_layer.weights = calloc(outputlen,sizeof(double*));
    n->output_layer.biases = calloc(outputlen,sizeof(double));
    for(i = 0; i < outputlen; i++)
    {
        n->output_layer.biases[i] = 0;
        n->output_layer.weights[i] = calloc(hiddenlen,sizeof(double));
        for(size_t j = 0; j < hiddenlen; j++)
        {
            n->output_layer.weights[i][j] = 1;
        }
    }

    return n;
}

void free_mlp(mlp* network)
{
    free_layer(network->input_layer);
    free_layer(network->hidden_layer);
    free_layer(network->output_layer);
    free(network);
}

unsigned char compute(mlp* network, double* input, size_t len)
{
    double *layer1, *layer2, *layer3;
    
    layer1 = calloc(network->input_layer.w, sizeof(double));
    compute_output(network->input_layer, input, layer1);
    
    layer2 = calloc(network->hidden_layer.w, sizeof(double));
    compute_output(network->hidden_layer, layer1, layer2);
    free(layer1);
    
    layer3 = calloc(network->output_layer.w,sizeof(double));
    compute_output(network->output_layer, layer2, layer3);
    free(layer2);
    
    unsigned char res = 0;
    for(unsigned char i = 1; i < network->output_layer.w; i++)
    {
        if (layer3[res] < layer3[i])
            res = i;
    }
    free(layer3);

    return res;
}

mlp* import_mlp(char* source)
{
    mlp* n;
    FILE* file = fopen(source,"rb");


    //allocate memory for the mlp
    n = calloc(1,sizeof(mlp));

    //read layer lengths from source into corresponding res fields
    fread(&n->input_layer.w, sizeof(size_t), 1, file);
    fread(&n->hidden_layer.w, sizeof(size_t), 1, file);
    fread(&n->output_layer.w, sizeof(size_t), 1, file);
    n->input_layer.h = 1;
    n->hidden_layer.h = n->input_layer.w;
    n->output_layer.h = n->hidden_layer.w;

    size_t x, y, i;

    //initialize and complete input_layer

    x = n->input_layer.w;
    y = n->input_layer.h;
    n->input_layer.biases = calloc(x, sizeof(double));
    n->input_layer.weights = calloc(x, sizeof(double*));
    for(i = 0; i < x; i++)
    {
        fread(&n->input_layer.biases[i],sizeof(double),1,file);
        n->input_layer.weights[i] = calloc(y, sizeof(double));
        fread(n->input_layer.weights[i], sizeof(double), y, file);
    }

    //initalize and complete hidden_layer

    x = n->hidden_layer.w;
    y = n->hidden_layer.h;
    n->hidden_layer.biases = calloc(x, sizeof(double));
    n->hidden_layer.weights = calloc(x,sizeof(double*));
    for(i = 0; i < x; i++)
    {
        fread(&n->hidden_layer.biases[i],sizeof(double),1,file);
        n->hidden_layer.weights[i] = calloc(y,sizeof(double));
        fread(n->hidden_layer.weights[i], sizeof(double), y, file);
    }

    //initialize and complete output_layer

    x = n->output_layer.w;
    y = n->output_layer.h;
    n->output_layer.biases = calloc(x, sizeof(double));
    n->output_layer.weights = calloc(x,sizeof(double*));
    for(i = 0; i < x; i++)
    {
        fread(&n->output_layer.biases[i],sizeof(double), 1, file);
        n->output_layer.weights[i] = calloc(y,sizeof(double));
        fread(n->output_layer.weights[i], sizeof(double), y, file);
    }

    fclose(file);
    return n;
}

void export_mlp(mlp* n, char* destination)
{
    FILE* file;
    file = fopen(destination, "wb");

    //write layer lengths
    fwrite(&n->input_layer.w, sizeof(size_t), 1, file);
    fwrite(&n->hidden_layer.w, sizeof(size_t), 1, file);
    fwrite(&n->output_layer.w, sizeof(size_t), 1, file);

    size_t m, i;

    //write weights for each layer
    m = n->input_layer.w;
    for(i = 0; i < m; i++)
    {
        fwrite(&n->input_layer.biases[i], sizeof(double), 1, file);
        fwrite(n->input_layer.weights[i], sizeof(double), n->input_layer.h, file);
    }
    m = n->hidden_layer.w;
    for(i = 0; i < m; i++)
    {
        fwrite(&n->hidden_layer.biases[i], sizeof(double), 1, file);
        fwrite(n->hidden_layer.weights[i], sizeof(double), n->hidden_layer.h, file);
    }
    m = n->output_layer.w;
    for(i = 0; i < m; i++)
    {
        fwrite(&n->output_layer.biases[i], sizeof(double), 1, file);
        fwrite(n->output_layer.weights[i], sizeof(double), n->output_layer.h, file);
    }
    
    fclose(file);
}

void print_mlp(mlp* n)
{
    printf("\ninput layer:\n");
    printf("length : %zu\n", n->input_layer.w);
    for(size_t i = 0; i < n->input_layer.w; i++)
    {
        printf("sigmoid %zu: ", i);
        printf("\n\tbias: %g\n\tweights: ", n->input_layer.biases[i]);
        printf("%g ", n->input_layer.weights[i][0]);
        printf("\n");
    }

    printf("\nhidden layer:\n");
    printf("length : %zu\n", n->hidden_layer.w);

    for(size_t i = 0; i < n->hidden_layer.w; i++)
    {
        printf("sigmoid %zu: ", i);
        printf("\n\tbias: %g\n\tweights: ", n->hidden_layer.biases[i]);
        for(size_t j = 0; j < n->input_layer.w; j++)
        {
            printf("%g ", n->hidden_layer.weights[i][j]);
        }
        printf("\n");
    }


    printf("\noutput layer:\n");
    printf("length : %zu\n", n->output_layer.w);

    for(size_t i = 0; i < n->output_layer.w; i++)
    {
        printf("sigmoid %zu: ", i);
        printf("\n\tbias: %g\n\tweights: ", n->output_layer.biases[i]);
        for(size_t j = 0; j < n->hidden_layer.w; j++)
        {
            printf("%g ", n->output_layer.weights[i][j]);
        }
        printf("\n");
    }
}
