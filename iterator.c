#include "includes/iterator.h"
#include <stdlib.h>

Iterator iterator_create(void *ptr, size_t size, size_t count, enum iterator_type type) {
  Iterator iter = NULL;

  if (!ptr || !size)
    return NULL;

  iter = malloc(sizeof(struct iterator_s));
  if (!iter)
    return NULL;

  iter->ptr = ptr;
  iter->value = NULL;
  iter->size = size;
  iter->count = count;
  iter->index = -1;
  iter->type = type;

  return iter;
}

void *iterator_next(Iterator iterator) {
	void *ptr = NULL;

  if (!iterator)
    return NULL;

  iterator->index++;
  if (iterator->index >= iterator->count)
  	return NULL;

  if (iterator->type == I_ARR) {
		ptr = (char *)(iterator->ptr) + iterator->size * iterator->index;
		iterator->value = ptr;
	} else {
  	ptr = iterator->ptr + iterator->index;
  	iterator->value = *(void **)ptr;
	}

  return ptr;
}

int iterator_free(Iterator iterator) {
	if (!iterator)
		return 0;
	free(iterator);
	return 1;
}
