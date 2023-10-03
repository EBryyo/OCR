#include "layer.h"
#include "mlp.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

double randfrom(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

unsigned char maxindex(double* array, size_t len)
{
    //returns the index of the highest member of array
    unsigned char res = 0;
    for(unsigned char i = 1; i < len; i++)
    {
        if (array[res] < array[i])
            res = i;
    }
    free(array);
    return res;
}

mlp* init(size_t count, size_t* layers)
{
    //initializes an MLP with count layers, each layer with the appropriate 
    //number of neurons.
    mlp* n;

    //allocate memory for n and its layer array
    n = calloc(1,sizeof(mlp));
    n->count = count;
    n->layers = calloc(count, sizeof(Layer));
    
    //initialize first layer as passive layer.
    //height is not set, for it is not necessary to compute its output
    //biases and weights have no memory allocated to them for the same reason.
    n->layers[0].w = layers[0];
    n->layers[0].passive = 1;
    
    
    for(size_t i = 1; i < count; i++)
    {
        //each subsequent layer is not passive
        n->layers[i].passive = 0;
        
        //set number of neurons according to current count
        //and number of weights per neuron according to preceding neuron count
        n->layers[i].w = layers[i];
        n->layers[i].h = n->layers[i-1].w;
        
        //allocate memory for weights and biases
        n->layers[i].weights = calloc(layers[i], sizeof(double*));
        n->layers[i].biases = calloc(layers[i], sizeof(double));
        
        //configure each neuron's weights
        for(size_t j = 0; j < n->layers[i].w; j++)
        {
            //allocate memory for each neuron's weights
            n->layers[i].weights[j] = calloc(layers[i-1], sizeof(double));
            for (size_t k = 0; k < n->layers[i].h; k++)
            {
                //weight initialization is done here. 
                //figure something out if these need to be random. :3
                n->layers[i].weights[j][k] = randfrom(0,1);
            }
            n->layers[i].biases[j] = 0;
        }
    }
    
    //done :p
    return n;
}

void free_mlp(mlp* network)
{
    //frees all memory allocated to network, including its layers
    //and all of their weights and biases
    for(size_t i = 0; i < network->count; i++)
    {
        free_layer(network->layers[i]);
    }
    free(network->layers);
    free(network);
}

double** compute(mlp* network, double* input)
{
    double **res;
    double *i, *o;
    
    //allocate memory for each active layer's output
    res = calloc(network->count - 1, sizeof(double*));

    //allocate memory for both i and o 
    //i will be used as the input for each layer iterated on
    //o will be used as the output for each layer iterated on
    i = calloc(network->layers[0].w, sizeof(double));
    o = calloc(network->layers[1].w, sizeof(double));

    //copy input array into i, basically emulating the compute_output function
    //of a passive layer which makes that function kind of irrelevant but im
    //keeping it anyways ^^
    memcpy(i, input, network->layers[0].w * sizeof(double));
    
    for(size_t k = 1; k < network->count; k++)
    {
        //compute output into i
        compute_output(network->layers[k], i, o);
        if (k == 1)
            free(i);
        //memory allocated to i is no longer needed after o is determined,
        //and it will need to be resized, so it is freed
        //free(i);

        //insert the kth layer's outputs into res
        res[k-1] = o;
        
        //o becomes the next iteration's i 
        i = o;

        //memory is allocated for the next iteration
        o = calloc(network->layers[k].w, sizeof(double));
    }
    
    //i is not freed, for it points to res[network->count-1]
    //o, however, is not necessary, so it is freed
    free(o);
    return res;
}

mlp* import_mlp(char* source)
{
    mlp* n;
    Layer* l;
    size_t i, w, h;
    FILE* file = fopen(source,"rb");
    
    //exit clause
    if (file == NULL)
    {
        printf("binary file must exist.");
        return n;
    }

    //allocate memory for n
    n = calloc(1, sizeof(mlp));

    //read layer count from file
    fread(&n->count, sizeof(size_t), 1, file);

    //allocate memory for layer count
    n->layers = calloc(n->count, sizeof(Layer));

    //configure input layer
    fread(&n->layers[0].w, sizeof(size_t), 1, file);
    n->layers[0].passive = 1;

    //configure following layers
    for(i = 1; i < n->count; i++)
    {
        //set pointer to current layer for readability
        l = &n->layers[i];
        
        //set neuron count for current layer
        fread(&l->w, sizeof(size_t), 1, file);
        
        //set weight count per layer for current layer
        //weight count is previous layer's neuron count
        l->h = n->layers[i-1].w;
        
        //set current layer to active
        l->passive = 0;

        //allocate memory for biases and weights
        l->biases = calloc(l->w, sizeof(double));
        l->weights = calloc(l->w, sizeof(double*));
        
        //read biases into layer's biases array
        fread(l->biases, sizeof(double), l->w, file);
        
        //set each neuron's weights
        for(w = 0; w < l->w; w++)
        {
            //allocate memory for current neuron's weights
            l->weights[w] = calloc(l->h, sizeof(double));
            
            //read current neuron's weights into current layer's weights array
            fread(l->weights[w], sizeof(double), l->h, file);
        }
    }

    fclose(file);
    return n;
}

void export_mlp(mlp* n, char* destination)
{
    FILE* file;
    file = fopen(destination, "wb");
    size_t i, w, h;

    //write layer count into file
    
    fwrite(&n->count, sizeof(size_t), 1, file);

    //write input layer neuron count into file
    
    fwrite(&n->layers[0].w, sizeof(size_t), 1, file);
    
    //for each layer, write count, biases and weights
    //first the neuron count of the layer is written in file
    //then the entire biases array is written in file
    //then the weights matrix is written column by column in file
    
    for(i = 1; i < n->count; i++)
    {
        fwrite(&n->layers[i].w, sizeof(size_t), 1, file);
        fwrite(n->layers[i].biases, sizeof(double), n->layers[i].w, file);
        h = n->layers[i].h;
        for(w = 0; w < n->layers[i].w; w++)
        {
            fwrite(n->layers[i].weights[w], sizeof(double), h, file);
        }
    }

    fclose(file);
}

void print_mlp(mlp* n)
{
    size_t w,h;

    printf("MULTI-LAYER PERCEPTRON\n");
    printf("\nLAYER 0\n");
    printf("\nCOUNT : %zu\n\n", n->layers[0].w);
    

    for(size_t i = 1; i < n->count; i++)
    {
        printf("LAYER %zu\n\n", i);
        printf("COUNT : %zu\n\n", n->layers[i].w); 
        for(w = 0; w < n->layers[i].w; w++)
        {
            printf("sigmoid %zu :\n", w);
            printf("\tbias : %2g\n", n->layers[i].biases[w]);
            printf("\tweights : ");
            for(h = 0; h < n->layers[i].h; h++)
            {
                printf("%2g ", n->layers[i].weights[w][h]);
            }
            printf("\n");
        }
        printf("\n");
    }
}
