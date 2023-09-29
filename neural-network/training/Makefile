test: test.c ../structures/mlp.c ../structures/layer.c
	gcc -o test test.c ../structures/mlp.c ../structures/layer.c -lm

train: training.c ../structures/mlp.c ../structures/layer.c
	gcc -o train training.c ../structures/mlp.c ../structures/layer.c -lm

clean:
	rm test train
