#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <stdio.h>

enum iterator_type { I_ARR, I_PTR2PTR };

typedef struct iterator_s {
  void *ptr;
  void *value;
  ssize_t index;
  size_t size;
  size_t count;
  enum iterator_type type;
} *Iterator;

Iterator iterator_create(void *ptr, size_t size, size_t count,
                         enum iterator_type iter_type);
void *iterator_next(Iterator iterator);
int iterator_free(Iterator iterator);

#endif
