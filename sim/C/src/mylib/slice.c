#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "common.c"

typedef struct {
  char *const pointer;
  size_t const len;
  size_t const item_size;
} Slice;

extern inline void const *get_item(Slice const slice, size_t const index) {
  // disable for performance
  assert(slice.pointer != NULL);
  assert(index < slice.len);
  return slice.pointer + index * (slice.item_size);
}

Slice copy_slice(Slice const slice) {

  char *const copy_ptr = (char *)malloc(slice.len * sizeof(slice.item_size));
  if (copy_ptr == NULL) {
    abort(); // Allocation failed!
  }
  memcpy(copy_ptr, slice.pointer, slice.len * sizeof(slice.item_size));

  return (Slice){
      .pointer = copy_ptr, .len = slice.len, .item_size = slice.item_size};
}

void qsort_slice(Slice const slice) {
  qsort(slice.pointer, slice.len, slice.item_size, double_compare);
}

Slice sorted_slice(Slice const slice) {
  Slice const copy = copy_slice(slice);
  qsort_slice(copy);

  return copy;
}

void free_slice(Slice const slice) { free(slice.pointer); }

Slice get_slice(Slice const slice, size_t low, size_t high) {
  return (Slice){.pointer = slice.pointer + low * slice.item_size,
                 .len = high - low,
                 .item_size = slice.item_size};
}
