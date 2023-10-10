CFLAGS= -g -fsanitize=address
LDFLAGS= -Wall -Wextra -Werror -g -fsanitize=address

init: init.c mlp/mlp.c layer/layer.c
	gcc -o $@ $^ -g -fsanitize=address -lm

train: train.c mlp/mlp.c layer/layer.c
	gcc -o $@ $^ -lm

test: test.c mlp/mlp.c layer/layer.c
	gcc -o $@ $^ -lm

clean:
	rm init test train
