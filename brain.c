#include "includes/brain.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

Brain brain_define(size_t layers, size_t weights, size_t biases, va_list ap) {
  Brain brain = NULL;
  int i, size = 0;

  /* calculate structure size in bytes */
  size = sizeof(struct brain_s) + (layers + weights + biases) * sizeof(int);

  /* allocate structure */
  brain = calloc(size, 1);
  if (!brain)
    return NULL;

  /* define sections sizes */
  brain->layers_count = layers;
  brain->weights_count = weights;
  brain->biases_count = biases;
  brain->memory_size = 0;

  /* define sections pointers */
  brain->layers = (int *)((char *)brain + sizeof(struct brain_s));
  brain->biases = brain->layers + brain->layers_count;
  brain->weights = brain->biases + brain->biases_count;

  /* assign nodes count for each layer and calculate temp memory size */
  for (i = 0; i < brain->layers_count; i++) {
    int value = va_arg(ap, int);

    *(brain->layers + i) = value;
    if (value > brain->memory_size)
      brain->memory_size = value;
  }

  /* allocate temp memory */
  brain->memory = calloc(brain->memory_size, sizeof(int));
  if (!brain->memory) {
    free(brain);
    return NULL;
  }

  return brain;
}

Brain brain_create(int layers, ...) {
  va_list ap;
  Brain brain = NULL;
  int i = 0, weights = 0, biases = 0, last_inputs_count = 1;

  if (layers <= 0)
    return NULL;

  /* calculate structure information */
  va_start(ap, layers);
  for (i = 0; i < layers; i++) {
    int nodes = va_arg(ap, int);

    if (nodes <= 0) {
      va_end(ap);
      return NULL;
    }

    if (!i)
    	last_inputs_count = nodes;

    biases += nodes;
    weights += nodes * last_inputs_count;
    last_inputs_count = nodes;
  }
  va_end(ap);

  /* create and assign values to structure */
  va_start(ap, layers);
  brain = brain_define(layers, weights, biases, ap);
  va_end(ap);

  return brain;
}

int brain_solve_node(Brain brain, size_t size, int *inputs, int *weights,
                     int bias) {
  int i = 0, sum = bias;

  /* !TODO: validate arguments */
  for (i = 0; i < size; i++)
    sum += inputs[i] * weights[i];

  /* !TODO: apply activation function */
  return sum;
}

int brain_solve_layer(Brain brain, size_t size, int nodes, int *weights,
                       int *biases) {
  int i, *inputs;

  inputs = malloc(brain->memory_size * sizeof(int));
  if (!inputs)
  	return 0;
  memcpy(inputs, brain->memory, brain->memory_size * sizeof(int));

  /* !TODO: validate arguments */
  for (i = 0; i < nodes; i++) {
    brain->memory[i] = brain_solve_node(brain, size, inputs, weights, *biases);
    weights += size;
    biases++;
  }

  free(inputs);
  return 1;
}

int brain_feedforward(Brain brain, int *inputs) {
  int i, *weights, *biases;
  size_t size = brain_inputs(brain);

  if (!brain || !inputs)
    return 0;

  weights = brain->weights;
  biases = brain->biases;

  memset(brain->memory, 0, brain->memory_size * sizeof(int));
  memcpy(brain->memory, inputs, size * sizeof(int));

  for (i = 0; i < brain->layers_count; i++) {
    int nodes = *(brain->layers + i);

    if (!brain_solve_layer(brain, size, nodes, weights, biases))
    	return 0;
    biases += nodes;
    weights += nodes * size;
    size = nodes;
  }

  return 1;
}

void brain_free(Brain brain) {
  if (!brain)
    return;
  free(brain->memory);
  free(brain);
}
