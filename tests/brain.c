#include "../includes/brain.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_array(int *arr, size_t size) {
	int i;

	for (i = 0; i < size; i++)
		printf("%d, ", arr[i]);
	putchar(10);
}

int main(void) {
	int inputs[2] = {2, 3};
	int weights[] = {100, 200, 300, 400};
	int biases[] = {100, 50};

	Brain brain = brain_create(1, 2);
	if (!brain)
		exit(1);
	memcpy(brain->weights, weights, sizeof(int) * 4);
	memcpy(brain->biases, biases, sizeof(int) * 2);
	if (brain_feedforward(brain, inputs))
		print_array(brain->memory, brain_outputs(brain));
	brain_free(brain);
	return 0;
}
