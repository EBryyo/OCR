#ifndef TRAINING_H
#define TRAINING_H

double get_total_cost(double* output, double* target, size_t len, 
	double*** inertia);

void train(double* input, int target, Mlp* network,
	size_t len, double*** inertia);

#endif 
