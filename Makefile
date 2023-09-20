SRC := $(wildcard game/*.c)
OBJ := $(patsubst game/%.c, build/%.o, $(SRC))

.PHONY: run

cping_pong: $(OBJ) build/main.o
	gcc -Wall -lraylib -o $@ $^

build/main.o: main.c
	gcc -Wall -c $< -o $@

build/%.o: game/%.c
	gcc -Wall -c $< -o $@

run: cping_pong
	@./cping_pong
