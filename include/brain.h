#ifndef __AI_H__
#define __AI_H__

#include <stddef.h>

#define brain_inputs(brain) (brain->layers[0])
#define brain_outputs(brain)                                                   \
  (brain->layers_count == 1 ? brain_inputs(brain)                              \
                            : brain->layers[brain->layers_count - 1])

typedef struct brain_s {
  size_t layers_count;
  size_t biases_count;
  size_t weights_count;
  size_t memory_size;
  int *layers;
  int *biases;
  int *weights;
  int *memory;
} *Brain;

Brain brain_create(int layers, ...);
int brain_feedforward(Brain brain, int *inputs);
int brain_train(Brain brain, int dx, int dy, int direction);
int brain_save(Brain brain, char *filename);
Brain *brain_load(char *filename);
void brain_free(Brain brain);

#endif
