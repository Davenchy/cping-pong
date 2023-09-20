#include "../includes/iterator.h"
#include <stdio.h>

int main() {
  Iterator iter;
  int data[] = {10, 5, 6, 8, 9};

  iter = iterator_create(data, sizeof(int), sizeof(data) / sizeof(data[0]),
                         I_ARR);
  while (iterator_next(iter))
    printf("%ld: %d\n", iter->index, *(int *)iter->value);

  iterator_free(iter);
  return 0;
}
