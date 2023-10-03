test: test.c ../structures/mlp.c ../structures/layer.c
	gcc -o test test.c ../structures/mlp.c ../structures/layer.c -fsanitize=address -static-libasan -g -lm

train: train_ocr.c training.c ../structures/mlp.c ../structures/layer.c
	gcc -o train train_ocr.c training.c ../structures/mlp.c ../structures/layer.c -fsanitize=address -static-libasan -g -lm

clean:
	rm test train
