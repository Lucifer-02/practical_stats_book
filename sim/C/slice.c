#include <assert.h>
#include <stddef.h>

typedef struct {
  void const *pointer;
  size_t const len;
  size_t const item_size;
} Slice;

extern void const *get_item(Slice const slice, size_t const index) {
  assert(index < slice.len);
  return slice.pointer + index * (slice.item_size);
}
