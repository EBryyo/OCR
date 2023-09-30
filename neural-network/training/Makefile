test: test.c ../structures/mlp.c ../structures/layer.c
	gcc -o test test.c ../structures/mlp.c ../structures/layer.c -lm

train: train_ocr.c training.c ../structures/mlp.c ../structures/layer.c
	gcc -o train train_ocr.c training.c ../structures/mlp.c ../structures/layer.c -lm

clean:
	rm test train
