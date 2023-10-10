init: executables/init.c layer/layer.c mlp/mlp.c
	gcc -o $@ $^ -g -fsanitize=address -lm

train: executables/train.c mlp/mlp.c layer/layer.c
	gcc -o $@ $^ -g -fsanitize=address -lm

test: executables/test.c layer/layer.c mlp/mlp.c
	gcc -o $@ $^ -g -fsanitize=address -lm

clean:
	rm init test train
